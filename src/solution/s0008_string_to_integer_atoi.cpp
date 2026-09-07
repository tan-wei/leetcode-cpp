/**
 * File              : s0008_string_to_integer_atoi.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-07 19:38:08
 * Last Modified Date: 2026-09-07 19:48:39
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0008] String to Integer (atoi)
 *
 * Implement the myAtoi(string s) function, which converts a string to a 32-bit
 * signed integer. The algorithm for myAtoi(string s) is as follows: Whitespace:
 * Ignore any leading whitespace (" "). Signedness: Determine the sign by
 * checking if the next character is '-' or '+', assuming positivity if neither
 * present. Conversion: Read the integer by skipping leading zeros until a
 * non-digit character is encountered or the end of the string is reached. If no
 * digits were read, then the result is 0. Rounding: If the integer is out of
 * the 32-bit signed integer range [-2^31, 2^31 - 1], then round the integer to
 * remain in the range. Specifically, integers less than -2^31 should be rounded
 * to -2^31, and integers greater than 2^31 - 1 should be rounded to 2^31 - 1.
 * Return the integer as the final result.
 *
 * Example 1:
 * Input: s = "42"
 * Output: 42
 * Explanation:
 * The underlined characters are what is read in and the caret is the current
 * reader position. Step 1: "42" (no characters read because there is no leading
 * whitespace)
 *          ^
 * Step 2: "42" (no characters read because there is neither a '-' nor '+')
 *          ^
 * Step 3: "42" ("42" is read in)
 *            ^
 * Example 2:
 * Input: s = " -042"
 * Output: -42
 * Explanation:
 * Step 1: "   -042" (leading whitespace is read and ignored)
 *             ^
 * Step 2: "   -042" ('-' is read, so the result should be negative)
 *              ^
 * Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)
 *                ^
 * Example 3:
 * Input: s = "1337c0d3"
 * Output: 1337
 * Explanation:
 * Step 1: "1337c0d3" (no characters read because there is no leading
 * whitespace)
 *          ^
 * Step 2: "1337c0d3" (no characters read because there is neither a '-' nor
 * '+')
 *          ^
 * Step 3: "1337c0d3" ("1337" is read in; reading stops because the next
 * character is a non-digit)
 *              ^
 * Example 4:
 * Input: s = "0-1"
 * Output: 0
 * Explanation:
 * Step 1: "0-1" (no characters read because there is no leading whitespace)
 *          ^
 * Step 2: "0-1" (no characters read because there is neither a '-' nor '+')
 *          ^
 * Step 3: "0-1" ("0" is read in; reading stops because the next character is a
 * non-digit)
 *           ^
 * Example 5:
 * Input: s = "words and 987"
 * Output: 0
 * Explanation:
 * Reading stops at the first non-digit character 'w'.
 *
 * Constraints:
 * 	0 <= s.length <= 200
 * 	s consists of English letters (lower-case and upper-case), digits (0-9), '
 * ', '+', '-', and '.'.
 *
 */

// problem: https://leetcode.com/problems/string-to-integer-atoi/
// discuss: https://leetcode.com/problems/string-to-integer-atoi/discuss/

#include <limits>
#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    int myAtoi(string s) {
        long long num = 0;
        auto positive = true;

        auto i = 0;

        while (i < s.length() && isspace(s[i])) {
            i++;
        }

        if (i == s.length()) {
            return 0;
        }

        if (s[i] == '+') {
            i++;
            positive = true;
        } else if (s[i] == '-') {
            i++;
            positive = false;
        } else if (!isdigit(s[i])) {
            return 0;
        }

        while (i < s.length() && isdigit(s[i])) {
            long long temp;
            num = num * 10 + s[i] - '0';
            i++;

            if (positive == false) {
                temp = -num;
            } else {
                temp = num;
            }

            if (temp < numeric_limits<int>::min()) {
                return numeric_limits<int>::min();
            } else if (temp > numeric_limits<int>::max()) {
                return numeric_limits<int>::max();
            }
        }

        if (positive == false) {
            num = -num;
        }

        return num;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0008, Example1) {
    Solution solution;

    auto s = "42"s;

    auto result = 42;

    EXPECT_EQ(solution.myAtoi(s), result);
}

TEST(Problem0008, Example2) {
    Solution solution;

    auto s = " -042"s;

    auto result = -42;

    EXPECT_EQ(solution.myAtoi(s), result);
}

TEST(Problem0008, Example3) {
    Solution solution;

    auto s = "1337c0d3"s;

    auto result = 1'337;

    EXPECT_EQ(solution.myAtoi(s), result);
}

TEST(Problem0008, Example4) {
    Solution solution;

    auto s = "0-1"s;

    auto result = 0;

    EXPECT_EQ(solution.myAtoi(s), result);
}

TEST(Problem0008, Example5) {
    Solution solution;

    auto s = "words and 987"s;

    auto result = 0;

    EXPECT_EQ(solution.myAtoi(s), result);
}

#endif
