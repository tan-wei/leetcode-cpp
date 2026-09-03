/**
 * File              : s0003_longest_substring_without_repeating_characters.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-02 21:33:13
 * Last Modified Date: 2026-09-03 19:32:06
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0003] Longest Substring Without Repeating Characters
 *
 * Given a string s, find the length of the longest substring without duplicate
 * characters.
 *
 * Example 1:
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3. Note that "bca" and
 * "cab" are also correct answers.
 * Example 2: Input: s = "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 * Example 3:
 * Input: s = "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 * Notice that the answer must be a substring, "pwke" is a subsequence and not a
 * substring.
 *
 * Constraints:
 * 	0 <= s.length <= 10^5
 * 	s consists of English letters, digits, symbols and spaces.
 *
 */

// problem:
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// discuss:
// https://leetcode.com/problems/longest-substring-without-repeating-characters/discuss/

#include <string>
#include <unordered_map>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    int lengthOfLongestSubstring(string s) {
        int count = 0;
        int max_count = 0;

        unordered_map<char, int> lookup_map;

        for (int i = 0; i < s.length(); i++) {
            if (lookup_map.contains(s[i])) {
                if (count < i - lookup_map[s[i]]) {
                    ++count;
                    if (count > max_count) {
                        max_count = count;
                    }
                } else {
                    count = i - lookup_map[s[i]];
                }

            } else {
                ++count;
                if (count > max_count) {
                    max_count = count;
                }
            }

            lookup_map[s[i]] = i;
        }

        return max_count;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0003, Example1) {
    Solution solution;

    auto s = "abcabcbb"s;

    auto result = 3;

    EXPECT_EQ(solution.lengthOfLongestSubstring(s), result);
}

TEST(Problem0003, Example2) {
    Solution solution;

    auto s = "bbbbb"s;

    auto result = 1;

    EXPECT_EQ(solution.lengthOfLongestSubstring(s), result);
}

TEST(Problem0003, Example3) {
    Solution solution;

    auto s = "pwwkew"s;

    auto result = 3;

    EXPECT_EQ(solution.lengthOfLongestSubstring(s), result);
}

#endif
