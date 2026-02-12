/**
 * File              : fetcher.h
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-02-12 15:06:15
 * Last Modified Date: 2026-02-12 15:06:43
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

#ifndef LEETCODE_CPP_SRC_FETCHER_H
#define LEETCODE_CPP_SRC_FETCHER_H

#pragma once

#include <optional>
#include <string>
#include <vector>

// Third-party headers
#include "nlohmann/json.hpp"

namespace fetcher {
using json = nlohmann::json;

struct CodeDefinition {
    std::string value;
    std::string text;
    std::string default_code;
};

struct Problem {
    std::string title;
    std::string title_slug;
    std::string content;
    std::vector<CodeDefinition> code_definition;
    std::string sample_test_case;
    std::string difficulty;
    int question_id;
    std::string return_type;
};

// Fetch the problems overview JSON (raw). Returns parsed JSON on success.
std::optional<json> get_problems_json();

// Fetch a single problem by frontend id and return a parsed `Problem`.
std::optional<Problem> get_problem_by_id(int frontend_question_id);

} // namespace fetcher

#endif /* !LEETCODE_CPP_SRC_FETCHER_H */
