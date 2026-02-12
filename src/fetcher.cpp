/**
 * File              : fetcher.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-02-12 15:07:22
 * Last Modified Date: 2026-02-12 15:10:00
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

#include <chrono>
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>
#include <thread>

// This project headers
#include "fetcher.h"

using json = nlohmann::json;

static size_t write_callback(char* ptr, size_t size, size_t nmemb,
                             void* userdata) {
    std::string* s = static_cast<std::string*>(userdata);
    size_t total = size * nmemb;
    s->append(ptr, total);
    return total;
}

static std::optional<std::string> http_get(
    const std::string& url, struct curl_slist* headers = nullptr) {
    const int MAX_ATTEMPTS = 3;
    for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            return std::nullopt;
        }
        std::string resp;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // enable automatic decompression for supported encodings
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
        // prefer HTTP/2 over TLS
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        const char* dbg = std::getenv("FETCHER_DEBUG");
        if (dbg && std::string(dbg) == "1") {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }
        CURLcode rc = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (rc == CURLE_OK) {
            return resp;
        }
        if (attempt < MAX_ATTEMPTS) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(100 * (1 << (attempt - 1))));
        }
    }
    return std::nullopt;
}

static std::optional<std::string> http_post_json(
    const std::string& url, const std::string& body,
    struct curl_slist* headers = nullptr) {
    const int MAX_ATTEMPTS = 3;
    for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            return std::nullopt;
        }
        std::string resp;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // enable automatic decompression for supported encodings
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
        // prefer HTTP/2 over TLS
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,
                         static_cast<long>(body.size()));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        const char* dbg = std::getenv("FETCHER_DEBUG");
        if (dbg && std::string(dbg) == "1") {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }
        CURLcode rc = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (rc == CURLE_OK) {
            return resp;
        }
        if (attempt < MAX_ATTEMPTS) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(100 * (1 << (attempt - 1))));
        }
    }
    return std::nullopt;
}

namespace fetcher {

static const char* PROBLEMS_URL =
    "https://leetcode.com/api/problems/algorithms/";
static const char* GRAPHQL_URL = "https://leetcode.com/graphql";

std::optional<json> get_problems_json() {
    struct curl_slist* headers = nullptr;
    const char* cookie = std::getenv("LEETCODE_COOKIE");
    if (!cookie) {
        std::cerr << "Please set LEETCODE_COOKIE in .env file or environment\n";
        return std::nullopt;
    }
    headers = curl_slist_append(
        headers,
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
    // let libcurl set Accept-Encoding based on its supported features
    headers = curl_slist_append(
        headers, "Accept-Language: zh-CN,en-US;q=0.7,en;q=0.3");
    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(
        headers,
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:126.0) Gecko/20100101 Firefox/126.0");
    headers = curl_slist_append(headers, "Sec-Fetch-Dest: document");
    headers = curl_slist_append(headers, "Sec-Fetch-Mode: navigate");
    headers = curl_slist_append(headers, "Sec-Fetch-Site: none");
    headers = curl_slist_append(headers, "Sec-Fetch-User: ?1");
    headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1");
    headers = curl_slist_append(headers, "Host: leetcode.com");
    headers = curl_slist_append(headers, "TE: trailers");
    headers = curl_slist_append(headers, "Priority: u=1");
    std::string cook = std::string("Cookie: ") + cookie;
    headers = curl_slist_append(headers, cook.c_str());
    auto resp = http_get(PROBLEMS_URL, headers);
    if (!resp) {
        return std::nullopt;
    }
    try {
        json j = json::parse(*resp);
        return j;
    } catch (...) {
        return std::nullopt;
    }
}

static std::vector<CodeDefinition> parse_code_definitions(const json& cdj) {
    std::vector<CodeDefinition> out;
    if (!cdj.is_array()) {
        return out;
    }
    for (auto& e : cdj) {
        CodeDefinition c;
        c.value = e.value("value", "");
        c.text = e.value("text", "");
        if (e.contains("defaultCode")) {
            c.default_code = e["defaultCode"].get<std::string>();
        } else if (e.contains("default_code")) {
            c.default_code = e["default_code"].get<std::string>();
        }
        out.push_back(std::move(c));
    }
    return out;
}

// cppcheck-suppress unusedFunction
std::optional<Problem> get_problem_by_id(int frontend_question_id) {
    auto problems_opt = get_problems_json();
    if (!problems_opt) {
        return std::nullopt;
    }
    json problems = *problems_opt;
    if (!problems.contains("stat_status_pairs")) {
        return std::nullopt;
    }
    for (auto& entry : problems["stat_status_pairs"]) {
        if (!entry.contains("stat")) {
            continue;
        }
        int entry_id = -1;
        if (entry["stat"].contains("frontend_question_id")) {
            entry_id = entry["stat"]["frontend_question_id"].get<int>();
        } else if (entry["stat"].contains("question_id")) {
            entry_id = entry["stat"]["question_id"].get<int>();
        }
        if (entry_id != frontend_question_id) {
            continue;
        }
        if (entry.value("paid_only", false)) {
            return std::nullopt;
        }

        // GraphQL query body
        json query;
        query["operationName"] = "questionData";
        query["query"] =
            "query questionData($titleSlug: String!) { question(titleSlug: $titleSlug) { content stats codeDefinition sampleTestCase metaData }}";
        std::string titleSlug = entry["stat"].value("question__title_slug", "");
        query["variables"] = {{"titleSlug", titleSlug}};

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        const char* cookie = std::getenv("LEETCODE_COOKIE");
        if (!cookie) {
            return std::nullopt;
        }
        headers = curl_slist_append(
            headers,
            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
        // let libcurl set Accept-Encoding based on its supported features
        headers = curl_slist_append(
            headers, "Accept-Language: zh-CN,en-US;q=0.7,en;q=0.3");
        headers = curl_slist_append(headers, "Connection: keep-alive");
        headers = curl_slist_append(
            headers,
            "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:126.0) Gecko/20100101 Firefox/126.0");
        headers = curl_slist_append(headers, "Sec-Fetch-Dest: document");
        headers = curl_slist_append(headers, "Sec-Fetch-Mode: navigate");
        headers = curl_slist_append(headers, "Sec-Fetch-Site: none");
        headers = curl_slist_append(headers, "Sec-Fetch-User: ?1");
        headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1");
        headers = curl_slist_append(headers, "Host: leetcode.com");
        headers = curl_slist_append(headers, "TE: trailers");
        headers = curl_slist_append(headers, "Priority: u=1");
        std::string cook = std::string("Cookie: ") + cookie;
        headers = curl_slist_append(headers, cook.c_str());
        auto resp = http_post_json(GRAPHQL_URL, query.dump(), headers);
        if (!resp) {
            return std::nullopt;
        }
        try {
            json j = json::parse(*resp);
            const char* dbg = std::getenv("FETCHER_DEBUG");
            if (dbg && std::string(dbg) == "1") {
                std::cerr << "[fetcher] GraphQL response: " << j.dump(2)
                          << std::endl;
            }
            if (!j.contains("data") || !j["data"].contains("question")) {
                return std::nullopt;
            }
            json q = j["data"]["question"];
            Problem out;
            out.title = entry["stat"].value("question__title", "");
            out.title_slug = titleSlug;
            out.question_id = frontend_question_id;
            out.content = q.value("content", "");
            out.sample_test_case = q.value("sampleTestCase", "");
            // codeDefinition can be either a JSON array or a JSON-encoded
            // string
            json cdj = q.value("codeDefinition", json::array());
            if (cdj.is_string()) {
                try {
                    cdj = json::parse(cdj.get<std::string>());
                } catch (...) {
                    cdj = json::array();
                }
            }
            out.code_definition = parse_code_definitions(cdj);
            if (entry.contains("difficulty") &&
                entry["difficulty"].is_object() &&
                entry["difficulty"].contains("level")) {
                out.difficulty =
                    std::to_string(entry["difficulty"]["level"].get<int>());
            } else if (entry["difficulty"].is_string()) {
                out.difficulty = entry["difficulty"].get<std::string>();
            } else {
                out.difficulty = "";
            }
            // parse return type from metaData if available
            try {
                if (q.contains("metaData")) {
                    json md = json::parse(q["metaData"].get<std::string>());
                    if (md.contains("return") &&
                        md["return"].contains("type")) {
                        out.return_type =
                            md["return"]["type"].get<std::string>();
                    }
                }
            } catch (...) {
                out.return_type = "";
            }
            const char* dbg2 = std::getenv("FETCHER_DEBUG");
            if (dbg2 && std::string(dbg2) == "1") {
                std::cerr << "[fetcher] parsed problem: title_slug="
                          << out.title_slug << " id=" << out.question_id
                          << " code_defs=" << out.code_definition.size()
                          << " return_type=" << out.return_type << std::endl;
            }
            return out;
        } catch (...) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}

} // namespace fetcher
