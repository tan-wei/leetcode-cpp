/**
 * File              : s0022_generate_parentheses.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-21 07:31:13
 * Last Modified Date: 2026-09-21 07:50:43
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0022] Generate Parentheses
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 *
 * Constraints:
 * 	1 <= n <= 8
 *
 */

// problem: https://leetcode.com/problems/generate-parentheses/
// discuss: https://leetcode.com/problems/generate-parentheses/discuss/

#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if (n <= 0) {
            return {""};
        } else if (n == 1) {
            return {"()"};
        }

        vector<string> result;

        for (int i = 0; i < n; i++) {
            vector<string> result_i = generateParenthesis(i);
            vector<string> result_n_1_i = generateParenthesis(n - 1 - i);

            for (auto s_left : result_i) {
                for (auto s_right : result_n_1_i) {
                    result.emplace_back("(" + s_left + ")" + s_right);
                }
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0022, Example1) {
    Solution solution;

    auto n = 3;

    vector<string> result = {"((()))", "(()())", "(())()", "()(())", "()()()"};

    EXPECT_THAT(solution.generateParenthesis(n),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0022, Example2) {
    Solution solution;

    auto n = 1;

    vector<string> result = {"()"};

    EXPECT_THAT(solution.generateParenthesis(n),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
