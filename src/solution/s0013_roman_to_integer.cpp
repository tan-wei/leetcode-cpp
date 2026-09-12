/**
 * File              : s0013_roman_to_integer.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-12 23:11:52
 * Last Modified Date: 2026-09-12 23:32:29
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0013] Roman to Integer
 *
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D
 * and M. Symbol       Value I             1 V             5 X             10 L
 * 50 C             100 D             500 M             1000 For example, 2 is
 * written as II in Roman numeral, just two ones added together. 12 is written
 * as XII, which is simply X + II. The number 27 is written as XXVII, which is
 * XX + V + II. Roman numerals are usually written largest to smallest from left
 * to right. However, the numeral for four is not IIII. Instead, the number four
 * is written as IV. Because the one is before the five we subtract it making
 * four. The same principle applies to the number nine, which is written as IX.
 * There are six instances where subtraction is used: I can be placed before V
 * (5) and X (10) to make 4 and 9. X can be placed before L (50) and C (100) to
 * make 40 and 90. C can be placed before D (500) and M (1000) to make 400 and
 * 900. Given a roman numeral, convert it to an integer.
 *
 * Example 1:
 * Input: s = "III"
 * Output: 3
 * Explanation: III = 3.
 * Example 2:
 * Input: s = "LVIII"
 * Output: 58
 * Explanation: L = 50, V= 5, III = 3.
 * Example 3:
 * Input: s = "MCMXCIV"
 * Output: 1994
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 *
 * Constraints:
 * 	1 <= s.length <= 15
 * 	s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
 * 	It is guaranteed that s is a valid roman numeral in the range [1, 3999].
 *
 */

// problem: https://leetcode.com/problems/roman-to-integer/
// discuss: https://leetcode.com/problems/roman-to-integer/discuss/

#include <string>

using namespace std;

// submission codes start here

// submission codes end;

class Solution {
public:
    // cppcheck-suppress passedByValue
    int romanToInt(string s) {
        int result = 0;
        int cur = 0;
        while (cur < s.length()) {
            if (s[cur] == 'M') {
                result += 1'000;
                cur += 1;
            } else if (s[cur] == 'C' &&
                       cur + 1 < s.length() &&
                       s[cur + 1] == 'D') {
                result += 400;
                cur += 2;
            } else if (s[cur] == 'C' &&
                       cur + 1 < s.length() &&
                       s[cur + 1] == 'M') {
                result += 900;
                cur += 2;
            } else if (s[cur] == 'C') {
                result += 100;
                cur += 1;
            } else if (s[cur] == 'D') {
                result += 500;
                cur += 1;
            } else if (s[cur] == 'X' &&
                       cur + 1 < s.length() &&
                       s[cur + 1] == 'L') {
                result += 40;
                cur += 2;
            } else if (s[cur] == 'X' &&
                       cur + 1 < s.length() &&
                       s[cur + 1] == 'C') {
                result += 90;
                cur += 2;
            } else if (s[cur] == 'X') {
                result += 10;
                cur += 1;
            } else if (s[cur] == 'L') {
                result += 50;
                cur += 1;
            } else if (s[cur] == 'I' &&
                       cur + 1 < s.length() &&
                       s[cur + 1] == 'X') {
                result += 9;
                cur += 2;
            } else if (s[cur] == 'I' &&
                       cur + 1 < s.length() &&
                       s[cur + 1] == 'V') {
                result += 4;
                cur += 2;
            } else if (s[cur] == 'I') {
                result += 1;
                cur += 1;
            } else if (s[cur] == 'V') {
                result += 5;
                cur += 1;
            }
        }
        return result;
    }
};
#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0013, Example1) {
    Solution solution;

    auto s = "III"s;

    auto result = 3;

    EXPECT_EQ(solution.romanToInt(s), result);
}

TEST(Problem0013, Example2) {
    Solution solution;

    auto s = "LVIII"s;

    auto result = 58;

    EXPECT_EQ(solution.romanToInt(s), result);
}

TEST(Problem0013, Example3) {
    Solution solution;

    auto s = "MCMXCIV"s;

    auto result = 1'994;

    EXPECT_EQ(solution.romanToInt(s), result);
}

#endif
