/**
 * File              : s0005_longest_palindromic_substring.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-04 15:38:27
 * Last Modified Date: 2026-09-05 14:52:28
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0005] Longest Palindromic Substring
 *
 * Given a string s, return the longest palindromic substring in s.
 *
 * Example 1:
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 * Example 2:
 * Input: s = "cbbd"
 * Output: "bb"
 *
 * Constraints:
 * 	1 <= s.length <= 1000
 * 	s consist of only digits and English letters.
 *
 */

// problem: https://leetcode.com/problems/longest-palindromic-substring/
// discuss: https://leetcode.com/problems/longest-palindromic-substring/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    string longestPalindrome(string s) {
        if (s == string(s.rbegin(), s.rend())) {
            return s;
        }

        auto left = longestPalindrome(s.substr(1));
        auto right = longestPalindrome(s.substr(0, s.size() - 1));

        if (left.length() > right.length()) {
            return left;
        } else {
            return right;
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0005, Example1) {
    Solution solution;

    auto s = "babad"s;

    auto result = "bab"s;

    EXPECT_EQ(solution.longestPalindrome(s), result);
}

TEST(Problem0005, Example2) {
    Solution solution;

    auto s = "cbbd"s;

    auto result = "bb"s;

    EXPECT_EQ(solution.longestPalindrome(s), result);
}

TEST(Problem0005, TimeLimitExceededCase1) {
    GTEST_SKIP() << "TLE";

    Solution solution;

    auto s = "babaddtattarrattatddetartrateedredividerb"s;

    auto result = "bb"s;

    EXPECT_EQ(solution.longestPalindrome(s), result);
}

#endif
