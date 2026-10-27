/**
 * File              : s0058_length_of_last_word.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-27 20:08:50
 * Last Modified Date: 2026-10-27 20:22:03
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0058] Length of Last Word
 *
 * Given a string s consisting of words and spaces, return the length of the
 * last word in the string. A word is a maximal substring consisting of
 * non-space characters only.
 *
 * Example 1:
 * Input: s = "Hello World"
 * Output: 5
 * Explanation: The last word is "World" with length 5.
 * Example 2:
 * Input: s = "   fly me   to   the moon  "
 * Output: 4
 * Explanation: The last word is "moon" with length 4.
 * Example 3:
 * Input: s = "luffy is still joyboy"
 * Output: 6
 * Explanation: The last word is "joyboy" with length 6.
 *
 * Constraints:
 * 	1 <= s.length <= 10^4
 * 	s consists of only English letters and spaces ' '.
 * 	There will be at least one word in s.
 *
 */

// problem: https://leetcode.com/problems/length-of-last-word/
// discuss: https://leetcode.com/problems/length-of-last-word/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    int lengthOfLastWord(string s) {
        int len = 0, tail = s.length() - 1;

        while (tail >= 0 && s[tail] == ' ') {
            --tail;
        }

        while (tail >= 0 && s[tail] != ' ') {
            ++len;
            --tail;
        }

        return len;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0058, Example1) {
    Solution solution;

    auto s = "Hello World"s;

    auto result = 5;

    EXPECT_EQ(solution.lengthOfLastWord(s), result);
}

TEST(Problem0058, Example2) {
    Solution solution;

    auto s = "   fly me   to   the moon  "s;

    auto result = 4;

    EXPECT_EQ(solution.lengthOfLastWord(s), result);
}

TEST(Problem0058, Example3) {
    Solution solution;

    auto s = "luffy is still joyboy"s;

    auto result = 6;

    EXPECT_EQ(solution.lengthOfLastWord(s), result);
}

#endif
