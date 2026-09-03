/**
 * File              : main.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-02-12 17:15:14
 * Last Modified Date: 2026-09-03 10:33:01
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// This project headers
#include "fetcher.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

static void load_dotenv(const std::string& path = ".env") {
    std::ifstream f(path);
    if (!f) {
        return;
    }
    std::string line;
    auto trim = [](std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) {
            s.clear();
            return;
        }
        size_t b = s.find_last_not_of(" \t\r\n");
        s = s.substr(a, b - a + 1);
    };
    while (std::getline(f, line)) {
        auto pos = line.find('#');
        if (pos == 0) {
            continue;
        }
        if (pos != std::string::npos) {
            line.resize(pos);
        }
        trim(line);
        if (line.empty()) {
            continue;
        }
        auto eq = line.find('=');
        if (eq == std::string::npos) {
            continue;
        }
        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        trim(key);
        trim(val);
        if (val.size() >= 2 && ((val.front() == '"' && val.back() == '"') ||
                                (val.front() == '\'' && val.back() == '\''))) {
            val = val.substr(1, val.size() - 2);
        }
#ifdef _WIN32
        _putenv_s(key.c_str(), val.c_str());
#else
        setenv(key.c_str(), val.c_str(), 1);
#endif
    }
}

static int generate_random_id(const std::vector<int>& except_ids) {
    std::srand(static_cast<unsigned>(time(nullptr)));
    while (true) {
        int res = 1 + (std::rand() % 1'105);
        if (std::find(except_ids.begin(), except_ids.end(), res) ==
            except_ids.end()) {
            return res;
        }
    }
}

static std::string current_datetime() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

static std::vector<int> get_initialized_ids() {
    std::vector<int> out;
    fs::path dir = "./src/problem";
    if (!fs::exists(dir)) {
        return out;
    }
    std::regex r("p(\\d{4})_");
    for (auto& e : fs::directory_iterator(dir)) {
        if (!e.is_regular_file()) {
            continue;
        }
        std::smatch m;
        std::string name = e.path().filename().string();
        if (std::regex_search(name, m, r)) {
            out.push_back(std::stoi(m[1].str()));
        }
    }
    return out;
}

static std::string insert_return_in_code(const std::string& ret_type,
                                         const std::string& code) {
    std::string out = code;
    std::regex re("\\{[\\s\\n]*\\}");
    if (ret_type == "ListNode") {
        out = std::regex_replace(out, re, "{\n        return nullptr;\n    }");
    } else if (ret_type == "ListNode[]") {
        out = std::regex_replace(out, re, "{\n        return {};\n    }");
    } else if (ret_type == "TreeNode") {
        out = std::regex_replace(out, re, "{\n        return nullptr;\n    }");
    } else if (ret_type == "boolean") {
        out = std::regex_replace(out, re, "{\n        return false;\n    }");
    } else if (ret_type == "character") {
        out = std::regex_replace(out, re, "{\n        return '0';\n    }");
    } else if (ret_type == "character[][]") {
        out = std::regex_replace(out, re, "{\n        return {};\n    }");
    } else if (ret_type == "double") {
        out = std::regex_replace(out, re, "{\n        return 0.0;\n    }");
    } else if (ret_type == "double[]") {
        out = std::regex_replace(out, re, "{\n        return {};\n    }");
    } else if (ret_type == "int[]") {
        out = std::regex_replace(out, re, "{\n        return {};\n    }");
    } else if (ret_type == "integer" || ret_type == "int") {
        out = std::regex_replace(out, re, "{\n        return 0;\n    }");
    } else if (ret_type == "integer[]") {
        out = std::regex_replace(out, re, "{\n        return {};\n    }");
    } else if (ret_type.find("list<") != std::string::npos ||
               ret_type.find("[]") != std::string::npos) {
        out = std::regex_replace(out, re, "{\n        return {};\n    }");
    } else if (ret_type == "string") {
        out = std::regex_replace(
            out, re, "{\n        return std::string();\n    }");
    } else if (ret_type == "string[]") {
        out = std::regex_replace(out, re, "{\n        return {};\n    }");
    }
    return out;
}

static std::string parse_extra_use(const std::string& code) {
    std::string extra;
    bool has_list = code.find("ListNode") != std::string::npos;
    bool has_tree = code.find("TreeNode") != std::string::npos;
    if (has_list || has_tree) {
        extra += "// Utility headers\n";
    }
    if (has_list) {
        extra += "#include \"../util/linked_list.h\"\n";
    }
    if (has_tree) {
        extra += "#include \"../util/tree.h\"\n";
    }
    if (code.find("Point") != std::string::npos) {
        extra += "#include \"../util/point.h\"\n";
    }
    return extra;
}

static std::string parse_extra_using(const std::string& code) {
    std::string extra;
    if (code.find("ListNode") != std::string::npos) {
        extra += "using util::ListNode;\n";
    }
    if (code.find("TreeNode") != std::string::npos) {
        extra += "using util::TreeNode;\n";
    }
    return extra;
}

static std::string parse_gtest_extra(const std::string& code) {
    std::string extra;
    bool has_list = code.find("ListNode") != std::string::npos;
    bool has_tree = code.find("TreeNode") != std::string::npos;
    if (has_list || has_tree) {
        extra += "// gtest utility headers\n";
    }
    if (has_list) {
        extra += "#include \"../util/linked_list_gtest.h\"\n";
    }
    if (has_tree) {
        extra += "#include \"../util/tree_gtest.h\"\n";
    }
    return extra;
}

static std::string parse_std_headers(const std::string& code) {
    std::vector<std::pair<std::string, std::string>> mapping = {
        {"vector", "vector"},
        {"string", "string"},
        {"map", "map"},
        {"unordered_map", "unordered_map"},
        {"set", "set"},
        {"unordered_set", "unordered_set"},
        {"tuple", "tuple"},
        {"pair", "utility"},
        {"queue", "queue"},
        {"stack", "stack"},
        {"list", "list"},
        {"deque", "deque"},
        {"array", "array"},
        {"bitset", "bitset"},
        {"sort", "algorithm"},
        {"lower_bound", "algorithm"},
        {"upper_bound", "algorithm"},
        {"binary_search", "algorithm"},
        {"next_permutation", "algorithm"},
        {"reverse", "algorithm"},
        {"unique", "algorithm"},
        {"cout", "iostream"},
        {"cin", "iostream"},
        {"cerr", "iostream"},
        {"stringstream", "sstream"},
        {"istringstream", "sstream"},
        {"ostringstream", "sstream"},
        {"setw", "iomanip"},
        {"setfill", "iomanip"},
        {"setprecision", "iomanip"},
        {"function", "functional"},
        {"shared_ptr", "memory"},
        {"unique_ptr", "memory"},
        {"make_shared", "memory"},
        {"accumulate", "numeric"},
        {"iota", "numeric"},
        {"numeric_limits", "limits"},
        {"pow", "cmath"},
        {"sqrt", "cmath"},
        {"memset", "cstring"},
        {"memcpy", "cstring"},
        {"int64_t", "cstdint"},
        {"uint64_t", "cstdint"},
        {"size_t", "cstddef"},
        {"regex", "regex"},
        {"smatch", "regex"},
        {"regex_search", "regex"},
        {"enable_if", "type_traits"},
        {"is_same", "type_traits"}};

    std::set<std::string> headers;
    for (auto& pr : mapping) {
        try {
            std::regex r("\\b" + pr.first + "\\b");
            if (std::regex_search(code, r)) {
                headers.insert(pr.second);
            }
        } catch (...) {
            // ignore regex errors for safety
        }
    }

    if (headers.empty()) {
        headers.insert("iostream");
    }

    std::ostringstream oss;
    for (const auto& header : headers) {
        oss << "#include <" << header << ">\n";
    }
    return oss.str();
}

static std::string build_desc(const std::string& content) {
    // Remove HTML tags (with or without attributes) — handles <tag>, </tag>,
    // <tag attr="...">, <tag />
    static const std::regex re_tag(R"(</?[a-zA-Z][^>]*>)");
    // Replace <sup> with ^ (keep this specific one)
    std::string s = content;
    {
        size_t pos = 0;
        while ((pos = s.find("<sup>", pos)) != std::string::npos) {
            s.replace(pos, 5, "^");
            pos += 1;
        }
        pos = 0;
        while ((pos = s.find("</sup>", pos)) != std::string::npos) {
            s.replace(pos, 6, "");
        }
    }
    s = std::regex_replace(s, re_tag, "");

    // HTML entities
    std::vector<std::pair<std::string, std::string>> entities = {
        {"&amp;", "&"},          {"&nbsp;", " "},  {"&gt;", ">"},
        {"&lt;", "<"},           {"&quot;", "\""}, {"&minus;", "-"},
        {"&#39;", "'"},          {"&apos;", "'"},  {"&frasl;", "/"},
        {"&le;", "\u{2264}"},    // ≤
        {"&ge;", "\u{2265}"},    // ≥
        {"&ldquo;", "\u{201c}"}, // "
        {"&rdquo;", "\u{201d}"}, // "
        {"&thinsp;", " "},
    };
    for (auto& pr : entities) {
        size_t pos = 0;
        while ((pos = s.find(pr.first, pos)) != std::string::npos) {
            s.replace(pos, pr.first.size(), pr.second);
            pos += pr.second.size();
        }
    }

    // Collapse multiple newlines and format as comment lines
    {
        size_t p = 0;
        while ((p = s.find("\n\n", p)) != std::string::npos) {
            s.replace(p, 2, "\n");
        }
    }
    {
        std::string needle = "\n";
        std::string repl = "\n * ";
        size_t pos = 0;
        while ((pos = s.find(needle, pos)) != std::string::npos) {
            s.replace(pos, needle.size(), repl);
            pos += repl.size();
        }
    }
    return s;
}

static std::string trim_copy(const std::string& s) {
    size_t begin = s.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) {
        return {};
    }
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(begin, end - begin + 1);
}

static std::string collect_input(int argc, const char* const argv[]) {
    if (argc <= 1) {
        return {};
    }

    std::ostringstream oss;
    for (int index = 1; index < argc; ++index) {
        if (index > 1) {
            oss << ' ';
        }
        oss << argv[index];
    }
    return trim_copy(oss.str());
}

static void deal_solving(int id) {
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << id;
    std::string id4 = oss.str();
    std::string prefix = std::string("p") + id4 + "_";
    fs::path problem_dir = "./src/problem";
    if (!fs::exists(problem_dir)) {
        throw std::runtime_error("problem directory does not exist");
    }
    fs::path found;
    for (auto& e : fs::directory_iterator(problem_dir)) {
        if (!e.is_regular_file()) {
            continue;
        }
        std::string name = e.path().filename().string();
        if (name.rfind(prefix, 0) == 0) {
            found = e.path();
            break;
        }
    }
    if (found.empty()) {
        throw std::runtime_error("problem file not found");
    }
    std::string base = found.filename().string();
    std::string orig_base = base;
    if (base.size() > 4 && base.substr(base.size() - 4) == ".cpp") {
        base.resize(base.size() - 4);
    }
    if (base.size() > 0 && base[0] == 'p') {
        base[0] = 's';
    }
    fs::create_directories("./src/solution");
    fs::path solution_path = fs::path("./src/solution") / (base + ".cpp");
    if (fs::exists(solution_path)) {
        throw std::runtime_error("solution already exists");
    }
    fs::rename(found, solution_path);
    // Update the File header inside the moved file: replace orig filename with
    // new one
    try {
        std::ifstream in(solution_path);
        if (in) {
            std::ostringstream ss;
            ss << in.rdbuf();
            std::string content = ss.str();
            std::string orig_name = orig_base;
            size_t pos = content.find(orig_name);
            if (pos != std::string::npos) {
                std::string new_name = base + ".cpp";
                content.replace(pos, orig_name.length(), new_name);
                std::ofstream out(solution_path);
                out << content;
            }
        }
    } catch (...) {
        // ignore errors updating header
    }
}

static void deal_problem(const fetcher::Problem& problem,
                         const fetcher::CodeDefinition& code) {
    std::ostringstream fn;
    fn << "p" << std::setw(4) << std::setfill('0') << problem.question_id
       << "_";
    std::string slug = problem.title_slug;
    std::replace(slug.begin(), slug.end(), '-', '_');
    fn << slug;
    std::string file_name = fn.str();
    fs::path dir = "./src/problem";
    fs::create_directories(dir);
    fs::path file_path = dir / (file_name + ".cpp");
    if (fs::exists(file_path)) {
        throw std::runtime_error("problem already initialized");
    }

    // load template
    std::ifstream tmpl("../template.cpp");
    if (!tmpl) {
        tmpl.open("./template.cpp");
    }
    if (!tmpl) {
        throw std::runtime_error("template.cpp not found");
    }

    std::string tpl;

    {
        std::ostringstream ss;
        ss << tmpl.rdbuf();
        tpl = ss.str();
    }

    auto replace_all =
        [&](std::string& s, const std::string& a, const std::string& b) {
            size_t pos = 0;
            while ((pos = s.find(a, pos)) != std::string::npos) {
                s.replace(pos, a.length(), b);
                pos += b.length();
            }
        };

    std::string default_code =
        insert_return_in_code(problem.return_type, code.default_code);
    replace_all(tpl, "__PROBLEM_TITLE__", problem.title);
    replace_all(tpl, "__PROBLEM_DESC__", build_desc(problem.content));
    replace_all(tpl, "__PROBLEM_DEFAULT_CODE__", default_code);
    {
        std::ostringstream idbuf;
        idbuf << std::setw(4) << std::setfill('0') << problem.question_id;
        replace_all(tpl, "__PROBLEM_ID__", idbuf.str());
        // Replace file name placeholder with actual file name (pXXXX_slug.cpp)
        replace_all(tpl, "__FILE_NAME__", file_name + ".cpp");
    }
    replace_all(tpl, "__EXTRA_USE__", parse_extra_use(default_code));
    replace_all(tpl, "__EXTRA_USING__", parse_extra_using(default_code));
    replace_all(tpl, "__GTEST_EXTRA__", parse_gtest_extra(default_code));
    replace_all(tpl, "__STL_INCLUDES__", parse_std_headers(default_code));
    replace_all(tpl, "__PROBLEM_LINK__",
                std::string("https://leetcode.com/problems/") +
                    problem.title_slug +
                    "/");
    replace_all(tpl, "__DISCUSS_LINK__",
                std::string("https://leetcode.com/problems/") +
                    problem.title_slug +
                    "/discuss/");
    // fill template timestamps
    std::string now = current_datetime();
    replace_all(tpl, "__CREATE_DATE__", now);
    replace_all(tpl, "__LAST_MODIFIED_DATE__", now);

    std::ofstream out(file_path);
    out << tpl;
    out.close();
}

int main(int argc, char* argv[]) {
    std::cout << "Welcome to leetcode-cpp.\n";
    // load environment variables from ./ .env (simple local loader)
    load_dotenv();
    auto initialized = get_initialized_ids();
    std::string input = collect_input(argc, argv);
    if (input.empty()) {
        std::cout
            << "Please enter frontend problem id, or 'random', or 'all', or 'solve <id>':\n";
        if (!std::getline(std::cin, input)) {
            std::cerr << "No input provided.\n";
            return 1;
        }
        input = trim_copy(input);
    }

    if (input.empty()) {
        std::cerr
            << "Invalid command. Use a problem id, 'random', 'all', or 'solve <id>'.\n";
        return 1;
    }

    std::smatch m;
    std::regex solving_pattern("^solve (\\d+)$");
    if (std::regex_match(input, m, solving_pattern)) {
        int sid = std::stoi(m[1].str());
        try {
            deal_solving(sid);
            std::cout << "Moved problem " << sid << " to src/solution/.\n";
            return 0;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }
    if (input == "random") {
        int id = generate_random_id(initialized);
        input = std::to_string(id);
    }
    if (input == "all") {
        auto probs_json = fetcher::get_problems_json();
        if (!probs_json) {
            std::cerr << "Failed to fetch problems.\n";
            return 1;
        }
        // simple serial init for now
        for (auto& ps : (*probs_json)["stat_status_pairs"]) {
            int fid = ps["stat"].value("frontend_question_id", -1);
            if (fid == -1) {
                continue;
            }
            if (std::find(initialized.begin(), initialized.end(), fid) !=
                initialized.end()) {
                continue;
            }
            auto prob = fetcher::get_problem_by_id(fid);
            if (!prob) {
                continue;
            }
            if (prob->code_definition.empty()) {
                continue;
            }
            try {
                deal_problem(*prob, prob->code_definition[0]);
            } catch (const std::exception& e) {
                std::cerr << "Error initializing problem " << fid << ": "
                          << e.what() << "\n";
            }
        }
        return 0;
    }
    std::regex problem_id_pattern("^(\\d+)$");
    if (!std::regex_match(input, m, problem_id_pattern)) {
        std::cerr
            << "Invalid command. Use a problem id, 'random', 'all', or 'solve <id>'.\n";
        return 1;
    }

    int id = std::stoi(m[1].str());
    auto problem = fetcher::get_problem_by_id(id);
    if (!problem) {
        std::cerr << "Problem not found or paid-only.\n";
        return 1;
    }
    fetcher::CodeDefinition cd =
        problem->code_definition.empty() ? fetcher::CodeDefinition{}
                                         : problem->code_definition[0];
    try {
        deal_problem(*problem, cd);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    std::cout << "Wrote ./src/problem/p" << std::setw(4) << std::setfill('0')
              << problem->question_id << "_" << problem->title_slug << ".cpp\n";
    return 0;
}
