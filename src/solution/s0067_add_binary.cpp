/**
 * File              : s0067_add_binary.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-05 20:15:01
 * Last Modified Date: 2026-11-05 20:38:31
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0067] Add Binary
 *
 * Given two binary strings a and b, return their sum as a binary string.
 *
 * Example 1:
 * Input: a = "11", b = "1"
 * Output: "100"
 * Example 2:
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 *
 * Constraints:
 * 	1 <= a.length, b.length <= 10^4
 * 	a and b consist only of '0' or '1' characters.
 * 	Each string does not contain leading zeros except for the zero itself.
 *
 */

// problem: https://leetcode.com/problems/add-binary/
// discuss: https://leetcode.com/problems/add-binary/discuss/

#include <algorithm>
#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    string addBinary(string a, string b) {
        string result;
        int i = a.length() - 1;
        int j = b.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) {
                sum += a[i--] - '0';
            }
            if (j >= 0) {
                sum += b[j--] - '0';
            }
            carry = sum / 2;
            result.push_back((sum % 2) + '0');
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0067, Example1) {
    Solution solution;

    auto a = "11"s;
    auto b = "1"s;

    auto result = "100"s;

    EXPECT_EQ(solution.addBinary(a, b), result);
}

TEST(Problem0067, Example2) {
    Solution solution;

    auto a = "1010"s;
    auto b = "1011"s;

    auto result = "10101"s;

    EXPECT_EQ(solution.addBinary(a, b), result);
}

TEST(Problem0067, AdditionalTestZeroAddition) {
    Solution solution;

    auto a = "0"s;
    auto b = "0"s;

    auto result = "0"s;

    EXPECT_EQ(solution.addBinary(a, b), result);
}

TEST(Problem0067, AdditionalTestMultipleCarries) {
    Solution solution;

    auto a = "1111"s;
    auto b = "1111"s;

    auto result = "11110"s;

    EXPECT_EQ(solution.addBinary(a, b), result);
}

TEST(Problem0067, AdditionalTestDifferentLengths) {
    Solution solution;

    auto a = "1"s;
    auto b = "111"s;

    auto result = "1000"s;

    EXPECT_EQ(solution.addBinary(a, b), result);
}

TEST(Problem0067, AdditionalTestNoCarryOver) {
    Solution solution;

    auto a = "1010"s;
    auto b = "0101"s;

    auto result = "1111"s;

    EXPECT_EQ(solution.addBinary(a, b), result);
}

#endif
