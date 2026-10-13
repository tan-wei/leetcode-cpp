/**
 * File              : s0044_wildcard_matching.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-13 19:09:31
 * Last Modified Date: 2026-10-13 20:36:39
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0044] Wildcard Matching
 *
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*' where:
 * 	'?' Matches any single character.
 * 	'*' Matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 *
 * Example 1:
 * Input: s = "aa", p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 * Example 2:
 * Input: s = "aa", p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 * Example 3:
 * Input: s = "cb", p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not
 * match 'b'.
 *
 * Constraints:
 * 	0 <= s.length, p.length <= 2000
 * 	s contains only lowercase English letters.
 * 	p contains only lowercase English letters, '?' or '*'.
 *
 */

// problem: https://leetcode.com/problems/wildcard-matching/
// discuss: https://leetcode.com/problems/wildcard-matching/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    bool isMatch(string s, string p) { return false; }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0044, Example1) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = "aa"s;
    auto p = "a"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0044, Example2) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = "aa"s;
    auto p = "*"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0044, Example3) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = "cb"s;
    auto p = "?a"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

#endif
