/**
 * File              :
 * s0028_find_the_index_of_the_first_occurrence_in_a_string.cpp Project :
 * leetcode-cpp Author            : Wei Tan <tanwei.winterreise@gmail.com> Date
 * : 2026-09-27 17:13:02 Last Modified Date: 2026-09-27 17:16:38 Last Modified
 * By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0028] Find the Index of the First Occurrence in a String
 *
 * Given two strings needle and haystack, return the index of the first
 * occurrence of needle in haystack, or -1 if needle is not part of haystack.
 *
 * Example 1:
 * Input: haystack = "sadbutsad", needle = "sad"
 * Output: 0
 * Explanation: "sad" occurs at index 0 and 6.
 * The first occurrence is at index 0, so we return 0.
 * Example 2:
 * Input: haystack = "leetcode", needle = "leeto"
 * Output: -1
 * Explanation: "leeto" did not occur in "leetcode", so we return -1.
 *
 * Constraints:
 * 	1 <= haystack.length, needle.length <= 10^4
 * 	haystack and needle consist of only lowercase English characters.
 *
 */

// problem:
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
// discuss:
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    int strStr(string haystack, string needle) {
        auto hl = haystack.length();
        auto nl = needle.length();

        if (nl > hl) {
            return -1;
        }

        for (auto c = 0; c <= hl - nl; c++) {
            auto cur = 0;
            while ((cur < nl) &&
                   (cur + c < hl) &&
                   (haystack[c + cur] == needle[cur])) {
                ++cur;
            }

            if (cur == nl) {
                return c;
            }
        }

        return -1;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0028, Example1) {
    Solution solution;

    auto haystack = "sadbutsad"s;
    auto needle = "sad"s;

    auto result = 0;

    EXPECT_EQ(solution.strStr(haystack, needle), result);
}

TEST(Problem0028, Example2) {
    Solution solution;

    auto haystack = "leetcode"s;
    auto needle = "leeto"s;

    auto result = -1;

    EXPECT_EQ(solution.strStr(haystack, needle), result);
}

TEST(Problem0028, AdditionalCaseEqualStrings) {
    Solution solution;

    auto haystack = "hello"s;
    auto needle = "hello"s;

    EXPECT_EQ(solution.strStr(haystack, needle), 0);
}

TEST(Problem0028, AdditionalCaseNeedleAtEnd) {
    Solution solution;

    auto haystack = "hello"s;
    auto needle = "lo"s;

    EXPECT_EQ(solution.strStr(haystack, needle), 3);
}

TEST(Problem0028, AdditionalCaseSingleCharMatch) {
    Solution solution;

    auto haystack = "a"s;
    auto needle = "a"s;

    EXPECT_EQ(solution.strStr(haystack, needle), 0);
}

TEST(Problem0028, AdditionalCaseSingleCharNoMatch) {
    Solution solution;

    auto haystack = "a"s;
    auto needle = "b"s;

    EXPECT_EQ(solution.strStr(haystack, needle), -1);
}

TEST(Problem0028, AdditionalCaseNoMatchPrefixMismatch) {
    Solution solution;

    auto haystack = "mississippi"s;
    auto needle = "issip"s;

    EXPECT_EQ(solution.strStr(haystack, needle), 4);
}

TEST(Problem0028, AdditionalCaseRepeatedCharacters) {
    Solution solution;

    auto haystack = "aaaaa"s;
    auto needle = "bba"s;

    EXPECT_EQ(solution.strStr(haystack, needle), -1);
}

TEST(Problem0028, AdditionalCaseNeedleIsLonger) {
    Solution solution;

    auto haystack = "abc"s;
    auto needle = "abcd"s;

    EXPECT_EQ(solution.strStr(haystack, needle), -1);
}

#endif
