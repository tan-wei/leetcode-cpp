/**
 * File              : s0069_sqrtx.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-07 16:00:43
 * Last Modified Date: 2026-11-07 18:05:44
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0069] Sqrt(x)
 *
 * Given a non-negative integer x, return the square root of x rounded down to
 * the nearest integer. The returned integer should be non-negative as well. You
 * must not use any built-in exponent function or operator. For example, do not
 * use pow(x, 0.5) in c++ or x ** 0.5 in python.
 *
 * Example 1:
 * Input: x = 4
 * Output: 2
 * Explanation: The square root of 4 is 2, so we return 2.
 * Example 2:
 * Input: x = 8
 * Output: 2
 * Explanation: The square root of 8 is 2.82842..., and since we round it down
 * to the nearest integer, 2 is returned.
 *
 * Constraints:
 * 	0 <= x <= 2^31 - 1
 *
 */

// problem: https://leetcode.com/problems/sqrtx/
// discuss: https://leetcode.com/problems/sqrtx/discuss/

#include <iostream>

using namespace std;

// submission codes start here

class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }

        if (x >= 1 && x < 4) {
            return 1;
        }

        double result = x / 2.0;

        while (true) {
            result = result / 2.0 + x / result / 2.0;
            if (result * result - x < 1) {
                break;
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0069, Example1) {
    Solution solution;

    auto x = 4;

    auto result = 2;

    EXPECT_EQ(solution.mySqrt(x), result);
}

TEST(Problem0069, Example2) {
    Solution solution;

    auto x = 8;

    auto result = 2;

    EXPECT_EQ(solution.mySqrt(x), result);
}

TEST(Problem0069, AddtionalCaseCaseZero) {
    Solution solution;

    auto x = 0;

    auto result = 0;

    EXPECT_EQ(solution.mySqrt(x), result);
}

TEST(Problem0069, AddtionalCaseCaseOne) {
    Solution solution;

    auto x = 1;

    auto result = 1;

    EXPECT_EQ(solution.mySqrt(x), result);
}

TEST(Problem0069, AddtionalCaseCaseTwo) {
    Solution solution;

    auto x = 2;

    auto result = 1;

    EXPECT_EQ(solution.mySqrt(x), result);
}

TEST(Problem0069, AddtionalCaseCaseThree) {
    Solution solution;

    auto x = 3;

    auto result = 1;

    EXPECT_EQ(solution.mySqrt(x), result);
}

TEST(Problem0069, AddtionalCaseCaseLargeNormal) {
    Solution solution;

    auto x = 2'147'395'599;

    auto result = 46'339;

    EXPECT_EQ(solution.mySqrt(x), result);
}

TEST(Problem0069, AddtionalCaseCaseIntMax) {
    Solution solution;

    auto x = 2'147'483'647;

    auto result = 46'340;

    EXPECT_EQ(solution.mySqrt(x), result);
}

#endif
