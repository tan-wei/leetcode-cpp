/**
 * File              : s0012_integer_to_roman.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-11 23:16:33
 * Last Modified Date: 2026-09-11 23:26:14
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0012] Integer to Roman
 *
 * Seven different symbols represent Roman numerals with the following values:
 *
 *
 * 			Symbol
 * 			Value
 *
 *
 *
 *
 * 			I
 * 			1
 *
 *
 * 			V
 * 			5
 *
 *
 * 			X
 * 			10
 *
 *
 * 			L
 * 			50
 *
 *
 * 			C
 * 			100
 *
 *
 * 			D
 * 			500
 *
 *
 * 			M
 * 			1000
 *
 *
 * Roman numerals are formed by appending the conversions of decimal place
 * values from highest to lowest. Converting a decimal place value into a Roman
 * numeral has the following rules: If the value does not start with 4 or 9,
 * select the symbol of the maximal value that can be subtracted from the input,
 * append that symbol to the result, subtract its value, and convert the
 * remainder to a Roman numeral. If the value starts with 4 or 9 use the
 * subtractive form representing one symbol subtracted from the following
 * symbol, for example, 4 is 1 (I) less than 5 (V): IV and 9 is 1 (I) less than
 * 10 (X): IX. Only the following subtractive forms are used: 4 (IV), 9 (IX), 40
 * (XL), 90 (XC), 400 (CD) and 900 (CM). Only powers of 10 (I, X, C, M) can be
 * appended consecutively at most 3 times to represent multiples of 10. You
 * cannot append 5 (V), 50 (L), or 500 (D) multiple times. If you need to append
 * a symbol 4 times use the subtractive form. Given an integer, convert it to a
 * Roman numeral.
 *
 * Example 1:
 * Input: num = 3749
 * Output: "MMMDCCXLIX"
 * Explanation:
 * 3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
 *  700 = DCC as 500 (D) + 100 (C) + 100 (C)
 *   40 = XL as 10 (X) less of 50 (L)
 *    9 = IX as 1 (I) less of 10 (X)
 * Note: 49 is not 1 (I) less of 50 (L) because the conversion is based on
 * decimal places
 * Example 2:
 * Input: num = 58
 * Output: "LVIII" Explanation: 50 = L
 *  8 = VIII
 * Example 3:
 * Input: num = 1994
 * Output: "MCMXCIV"
 * Explanation:
 * 1000 = M
 *  900 = CM
 *   90 = XC
 *    4 = IV
 *
 * Constraints:
 * 	1 <= num <= 3999
 *
 */

// problem: https://leetcode.com/problems/integer-to-roman/
// discuss: https://leetcode.com/problems/integer-to-roman/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    string intToRoman(int num) {
        string result;

        while (num) {
            if (num >= 1'000) {
                result.append("M");
                num -= 1'000;
            } else if (num >= 900) {
                result.append("CM");
                num -= 900;
            } else if (num >= 500) {
                result.append("D");
                num -= 500;
            } else if (num >= 400) {
                result.append("CD");
                num -= 400;
            } else if (num >= 100) {
                result.append("C");
                num -= 100;
            } else if (num >= 90) {
                result.append("XC");
                num -= 90;
            } else if (num >= 50) {
                result.append("L");
                num -= 50;
            } else if (num >= 40) {
                result.append("XL");
                num -= 40;
            } else if (num >= 10) {
                result.append("X");
                num -= 10;
            } else if (num >= 9) {
                result.append("IX");
                num -= 9;
            } else if (num >= 5) {
                result.append("V");
                num -= 5;
            } else if (num >= 4) {
                result.append("IV");
                num -= 4;
            } else if (num >= 1) {
                result.append("I");
                num -= 1;
            } else {
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0012, Example1) {
    Solution solution;

    auto num = 3'749;

    auto result = "MMMDCCXLIX"s;

    EXPECT_EQ(solution.intToRoman(num), result);
}

TEST(Problem0012, Example2) {
    Solution solution;

    auto num = 58;

    auto result = "LVIII"s;

    EXPECT_EQ(solution.intToRoman(num), result);
}

TEST(Problem0012, Example3) {
    Solution solution;

    auto num = 1'994;

    auto result = "MCMXCIV"s;

    EXPECT_EQ(solution.intToRoman(num), result);
}

#endif
