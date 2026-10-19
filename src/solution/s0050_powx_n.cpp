/**
 * File              : s0050_powx_n.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-19 08:55:25
 * Last Modified Date: 2026-10-19 09:26:45
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0050] Pow(x, n)
 *
 * Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).
 *
 * Example 1:
 * Input: x = 2.00000, n = 10
 * Output: 1024.00000
 * Example 2:
 * Input: x = 2.10000, n = 3
 * Output: 9.26100
 * Example 3:
 * Input: x = 2.00000, n = -2
 * Output: 0.25000
 * Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25
 *
 * Constraints:
 * 	-100.0 < x < 100.0
 * 	-2^31 <= n <= 2^31-1
 * 	n is an integer.
 * 	Either x is not zero or n > 0.
 * 	-10^4 <= x^n <= 10^4
 *
 */

// problem: https://leetcode.com/problems/powx-n/
// discuss: https://leetcode.com/problems/powx-n/discuss/

#include <iostream>

using namespace std;

// submission codes start here

class Solution {
public:
    double myPow(double x, int n) {
        double result = 1;
        unsigned long long ln;

        if (n < 0) {
            ln = -n;
            x = 1 / x;
        } else {
            ln = n;
        }

        while (ln) {
            if (ln & 1) {
                result *= x;
            }
            x *= x;
            ln >>= 1;
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0050, Example1) {
    Solution solution;

    auto x = 2.00000;
    auto n = 10;

    auto result = 1024.00000;

    EXPECT_DOUBLE_EQ(solution.myPow(x, n), result);
}

TEST(Problem0050, Example2) {
    Solution solution;

    auto x = 2.10000;
    auto n = 3;

    auto result = 9.26100;

    EXPECT_DOUBLE_EQ(solution.myPow(x, n), result);
}

TEST(Problem0050, Example3) {
    Solution solution;

    auto x = 2.00000;
    auto n = -2;

    auto result = 0.25000;

    EXPECT_DOUBLE_EQ(solution.myPow(x, n), result);
}

#endif
