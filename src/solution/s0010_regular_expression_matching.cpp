/**
 * File              : s0010_regular_expression_matching.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-09 19:59:36
 * Last Modified Date: 2026-09-09 21:10:31
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0010] Regular Expression Matching
 *
 * Given an input string s and a pattern p, implement regular expression
 * matching with support for '.' and '*' where:
 * 	'.' Matches any single character.​​​​
 * 	'*' Matches zero or more of the preceding element.
 * Return a boolean indicating whether the matching covers the entire input
 * string (not partial).
 *
 * Example 1:
 * Input: s = "aa", p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 * Example 2:
 * Input: s = "aa", p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the preceding element, 'a'. Therefore,
 * by repeating 'a' once, it becomes "aa".
 * Example 3: Input: s = "ab", p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 *
 * Constraints:
 * 	1 <= s.length <= 20
 * 	1 <= p.length <= 20
 * 	s contains only lowercase English letters.
 * 	p contains only lowercase English letters, '.', and '*'.
 * 	It is guaranteed for each appearance of the character '*', there will be a
 * previous valid character to match.
 *
 */

// problem: https://leetcode.com/problems/regular-expression-matching/
// discuss: https://leetcode.com/problems/regular-expression-matching/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    bool isMatch(string s, string p) { return isMatchHelper(s, p, 0, 0); }

private:
    bool isMatchHelper(const string& s, const string& p, int ss, int ps) {
        int s_size = s.size();
        int p_size = p.size();

        if (p_size == ps) {
            return s_size == ss;
        }

        if (p[ps + 1] != '*') {
            if (ss < s_size && (p[ps] == s[ss] || p[ps] == '.')) {
                return isMatchHelper(s, p, ss + 1, ps + 1);
            }
        } else {
            if (isMatchHelper(s, p, ss, ps + 2)) {
                return true;
            }

            while (ss < s_size && (p[ps] == s[ss] || p[ps] == '.')) {
                if (isMatchHelper(s, p, ++ss, ps + 2)) {
                    return true;
                }
            }
        }

        return false;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0010, Example1) {
    Solution solution;

    auto s = "aa"s;
    auto p = "a"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, Example2) {
    Solution solution;

    auto s = "aa"s;
    auto p = "a*"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, Example3) {
    Solution solution;

    auto s = "ab"s;
    auto p = ".*"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase1) {
    Solution solution;

    auto s = "aa"s;
    auto p = "b"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase2) {
    Solution solution;

    auto s = "aa"s;
    auto p = "b*"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase3) {
    Solution solution;

    auto s = "aaa"s;
    auto p = "aaa*"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase4) {
    Solution solution;

    auto s = "aaa"s;
    auto p = "aab*"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase5) {
    Solution solution;

    auto s = "abc"s;
    auto p = "abc"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase6) {
    Solution solution;

    auto s = "abc"s;
    auto p = "abcd"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase7) {
    Solution solution;

    auto s = "a"s;
    auto p = "."s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase8) {
    Solution solution;

    auto s = "ab"s;
    auto p = ".b"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase9) {
    Solution solution;

    auto s = "abc"s;
    auto p = "..c"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase10) {
    Solution solution;

    auto s = "aab"s;
    auto p = "c*a*b"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase11) {
    Solution solution;

    auto s = "aaa"s;
    auto p = "a*a"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase12) {
    Solution solution;

    auto s = "aaa"s;
    auto p = "ab*a*c*a"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase13) {
    Solution solution;

    auto s = "ab"s;
    auto p = ".*"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase14) {
    Solution solution;

    auto s = ""s;
    auto p = ".*"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase15) {
    Solution solution;

    auto s = "abcdefg"s;
    auto p = ".*g"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase16) {
    Solution solution;

    auto s = "a"s;
    auto p = "ab*"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase17) {
    Solution solution;

    auto s = "ab"s;
    auto p = ".*c"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase18) {
    Solution solution;

    auto s = "aab"s;
    auto p = "a*a*b"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase19) {
    Solution solution;

    auto s = "aaaaaaaaaaaaab"s;
    auto p = "a*a*a*a*a*a*a*a*a*a*c"s;

    auto result = false;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

TEST(Problem0010, AdditionalCase20) {
    Solution solution;

    auto s = "bbbba"s;
    auto p = ".*a*a"s;

    auto result = true;

    EXPECT_EQ(solution.isMatch(s, p), result);
}

#endif
