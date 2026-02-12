/**
 * File              : main.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-02-12 17:15:14
 * Last Modified Date: 2026-02-12 18:58:37
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
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
    if (code.find("ListNode") != std::string::npos) {
        extra += "#include \"../util/linked_list.h\"\n";
        extra += "using util::ListNode;\n";
        extra += "using util::to_linked_list;\n";
        extra += "using util::to_vec;\n";
        extra += "using util::to_string;\n";
        extra += "using util::free_list;\n";
    }
    if (code.find("TreeNode") != std::string::npos) {
        extra += "#include \"../util/tree.h\"\n";
        extra += "using util::TreeNode;\n";
        extra += "using util::to_tree;\n";
        extra += "using util::to_level_list;\n";
        extra += "using util::to_string;\n";
        extra += "using util::free_tree;\n";
    }
    if (code.find("Point") != std::string::npos) {
        extra += "#include \"../util/point.h\"\n";
    }
    return extra;
}

static std::string build_desc(const std::string& content) {
    std::string s = content;
    std::vector<std::pair<std::string, std::string>> reps = {
        {"<strong>", ""}, {"</strong>", ""}, {"<strong class=\"example\">", ""},
        {"<em>", ""},     {"</em>", ""},     {"</p>", ""},
        {"<p>", ""},      {"<b>", ""},       {"</b>", ""},
        {"<pre>", ""},    {"</pre>", ""},    {"<ul>", ""},
        {"</ul>", ""},    {"<li>", ""},      {"</li>", ""},
        {"<code>", ""},   {"</code>", ""},   {"<i>", ""},
        {"</i>", ""},     {"<sub>", ""},     {"</sub>", ""},
        {"</sup>", ""},   {"<sup>", "^"},    {"&nbsp;", " "},
        {"&gt;", ">"},    {"&lt;", "<"},     {"&quot;", "\""},
        {"&minus;", "-"}, {"&#39;", "'"}};
    for (auto& pr : reps) {
        size_t pos = 0;
        while ((pos = s.find(pr.first, pos)) != std::string::npos) {
            s.replace(pos, pr.first.size(), pr.second);
            pos += pr.second.size();
        }
    }
    // collapse double newlines
    size_t p = 0;
    while ((p = s.find("\n\n", p)) != std::string::npos) {
        s.replace(p, 2, "\n");
    }
    // replace internal newlines with "\n * " (do not prefix the very first
    // line)
    std::string needle = "\n";
    std::string repl = "\n * ";
    size_t pos = 0;
    while ((pos = s.find(needle, pos)) != std::string::npos) {
        s.replace(pos, needle.size(), repl);
        pos += repl.size();
    }
    return s;
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
}

static void deal_problem(const fetcher::Problem& problem,
                         const fetcher::CodeDefinition& code,
                         bool write_mod_file) {
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
    }
    replace_all(tpl, "__EXTRA_USE__", parse_extra_use(default_code));
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

    (void)write_mod_file; // mod file generation intentionally disabled
}

int main() {
    std::cout << "Welcome to leetcode-cpp scaffold (translated).\n";
    // load environment variables from ./ .env (simple local loader)
    load_dotenv();
    auto initialized = get_initialized_ids();
    std::cout
        << "Please enter frontend problem id, or 'random', or 'all', or 'solve <id>':\n";
    std::string input;
    std::getline(std::cin, input);
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
                deal_problem(*prob, prob->code_definition[0], true);
            } catch (const std::exception& e) {
                std::cerr << "Error initializing problem " << fid << ": "
                          << e.what() << "\n";
            }
        }
        return 0;
    }
    int id = std::stoi(input);
    auto problem = fetcher::get_problem_by_id(id);
    if (!problem) {
        std::cerr << "Problem not found or paid-only.\n";
        return 1;
    }
    fetcher::CodeDefinition cd =
        problem->code_definition.empty() ? fetcher::CodeDefinition{}
                                         : problem->code_definition[0];
    try {
        deal_problem(*problem, cd, true);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    std::cout << "Wrote ./src/problem/p" << std::setw(4) << std::setfill('0')
              << problem->question_id << "_" << problem->title_slug << ".cpp\n";
    return 0;
}
