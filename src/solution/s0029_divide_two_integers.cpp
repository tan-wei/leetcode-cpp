/**
 * File              : s0029_divide_two_integers.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-28 18:41:54
 * Last Modified Date: 2026-09-28 19:17:49
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0029] Divide Two Integers
 *
 * Given two integers dividend and divisor, divide two integers without using
 * multiplication, division, and mod operator. The integer division should
 * truncate toward zero, which means losing its fractional part. For
 * example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
 * Return the quotient after dividing dividend by divisor.
 * Note: Assume we are dealing with an environment that could only store
 * integers within the 32-bit signed integer range: [-2^31, 2^31 - 1]. For this
 * problem, if the quotient is strictly greater than 2^31 - 1, then return 2^31
 * - 1, and if the quotient is strictly less than -2^31, then return -2^31.
 *
 * Example 1:
 * Input: dividend = 10, divisor = 3
 * Output: 3
 * Explanation: 10/3 = 3.33333.. which is truncated to 3.
 * Example 2:
 * Input: dividend = 7, divisor = -3
 * Output: -2
 * Explanation: 7/-3 = -2.33333.. which is truncated to -2.
 *
 * Constraints:
 * 	-2^31 <= dividend, divisor <= 2^31 - 1
 * 	divisor != 0
 *
 */

// problem: https://leetcode.com/problems/divide-two-integers/
// discuss: https://leetcode.com/problems/divide-two-integers/discuss/

#include <limits>

using namespace std;

// submission codes start here

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0 ||
            (dividend == std::numeric_limits<int>::min() && divisor == -1)) {
            return std::numeric_limits<int>::max();
        }

        bool sign = (dividend > 0) ^ (divisor > 0);
        unsigned int abs_divisor = (divisor < 0) ? -divisor : divisor;
        unsigned int abs_dividend = (dividend < 0) ? -dividend : dividend;
        int result = 0;

        for (int i = 31; i >= 0; i--) {
            if ((abs_dividend >> i) >= abs_divisor) {
                result = (result << 1) | 0x01;
                abs_dividend -= (abs_divisor << i);
            } else {
                result = result << 1;
            }
        }

        if (sign) {
            result = -result;
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0029, Example1) {
    Solution solution;

    auto dividend = 10;
    auto divisor = 3;

    auto result = 3;

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, Example2) {
    Solution solution;

    auto dividend = 7;
    auto divisor = -3;

    auto result = -2;

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseOverflowBoundary) {
    Solution solution;

    auto dividend = std::numeric_limits<int>::min(); // -2147483648
    auto divisor = -1;

    auto result = std::numeric_limits<int>::max(); // 2147483647

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseMinIntDividedByOne) {
    Solution solution;

    auto dividend = std::numeric_limits<int>::min();
    auto divisor = 1;

    auto result = std::numeric_limits<int>::min();

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseMinIntDividedBySelf) {
    Solution solution;

    auto dividend = std::numeric_limits<int>::min();
    auto divisor = std::numeric_limits<int>::min();

    auto result = 1;

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseBothNegative) {
    Solution solution;

    auto dividend = -10;
    auto divisor = -3;

    auto result = 3;

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseDividendIsZero) {
    Solution solution;

    auto dividend = 0;
    auto divisor = 1;

    auto result = 0;

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseDividendSmallerThanDivisor) {
    Solution solution;

    auto dividend = 3;
    auto divisor = 10;

    auto result = 0;

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseMaxIntOperationsPositive) {
    Solution solution;

    auto dividend = std::numeric_limits<int>::max();
    auto divisor = 1;

    auto result = std::numeric_limits<int>::max();

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

TEST(Problem0029, AdditionalCaseMaxIntOperationsNegative) {
    Solution solution;

    auto dividend = std::numeric_limits<int>::max();
    auto divisor = -1;

    auto result = -std::numeric_limits<int>::max();

    EXPECT_EQ(solution.divide(dividend, divisor), result);
}

#endif
