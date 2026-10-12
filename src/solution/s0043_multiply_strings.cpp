/**
 * File              : s0043_multiply_strings.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-12 19:37:30
 * Last Modified Date: 2026-10-12 22:14:44
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0043] Multiply Strings
 *
 * Given two non-negative integers num1 and num2 represented as strings, return
 * the product of num1 and num2, also represented as a string. Note: You must
 * not use any built-in BigInteger library or convert the inputs to integer
 * directly.
 *
 * Example 1:
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 * Example 2:
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 *
 * Constraints:
 * 	1 <= num1.length, num2.length <= 200
 * 	num1 and num2 consist of digits only.
 * 	Both num1 and num2 do not contain any leading zero, except the number 0
 * itself.
 *
 */

// problem: https://leetcode.com/problems/multiply-strings/
// discuss: https://leetcode.com/problems/multiply-strings/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    string multiply(string num1, string num2) {
        int l1 = num1.length();
        int l2 = num2.length();

        string result(l1 + l2, '0');

        for (int i = l1 - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = l2 - 1; j >= 0; j--) {
                int temp = result[i + j + 1] -
                           '0' +
                           (num1[i] - '0') * (num2[j] - '0') +
                           carry;
                carry = temp / 10;
                result[i + j + 1] = temp % 10 + '0';
            }

            result[i] += carry;
        }

        auto startpos = result.find_first_not_of("0");

        return string::npos != startpos ? result.substr(startpos) : string("0");
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0043, Example1) {
    Solution solution;

    auto num1 = "2"s;
    auto num2 = "3"s;

    auto result = "6"s;

    EXPECT_EQ(solution.multiply(num1, num2), result);
}

TEST(Problem0043, Example2) {
    Solution solution;

    auto num1 = "123"s;
    auto num2 = "456"s;

    auto result = "56088"s;

    EXPECT_EQ(solution.multiply(num1, num2), result);
}

#endif
