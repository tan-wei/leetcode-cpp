/**
 * File              : s0032_longest_valid_parentheses.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-01 09:45:52
 * Last Modified Date: 2026-10-01 16:56:53
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0032] Longest Valid Parentheses
 *
 * Given a string containing just the characters '(' and ')', return the length
 * of the longest valid (well-formed) parentheses substring.
 *
 * Example 1:
 * Input: s = "(()"
 * Output: 2
 * Explanation: The longest valid parentheses substring is "()".
 * Example 2:
 * Input: s = ")()())"
 * Output: 4
 * Explanation: The longest valid parentheses substring is "()()".
 * Example 3:
 * Input: s = ""
 * Output: 0
 *
 * Constraints:
 * 	0 <= s.length <= 3 * 10^4
 * 	s[i] is '(', or ')'.
 *
 */

// problem: https://leetcode.com/problems/longest-valid-parentheses/
// discuss: https://leetcode.com/problems/longest-valid-parentheses/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    int longestValidParentheses(string s) { return 0; }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0032, Example1) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = "(()"s;

    auto result = 2;

    EXPECT_EQ(solution.longestValidParentheses(s), result);
}

TEST(Problem0032, Example2) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = ")()())"s;

    auto result = 4;

    EXPECT_EQ(solution.longestValidParentheses(s), result);
}

TEST(Problem0032, Example3) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = ""s;

    auto result = 0;

    EXPECT_EQ(solution.longestValidParentheses(s), result);
}

#endif
