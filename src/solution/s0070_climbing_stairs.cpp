/**
 * File              : s0070_climbing_stairs.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-08 09:53:17
 * Last Modified Date: 2026-11-08 10:42:19
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0070] Climbing Stairs
 *
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can
 * you climb to the top?
 *
 * Example 1:
 * Input: n = 2
 * Output: 2
 * Explanation: There are two ways to climb to the top.
 * 1. 1 step + 1 step
 * 2. 2 steps
 * Example 2:
 * Input: n = 3
 * Output: 3
 * Explanation: There are three ways to climb to the top.
 * 1. 1 step + 1 step + 1 step
 * 2. 1 step + 2 steps
 * 3. 2 steps + 1 step
 *
 * Constraints:
 * 	1 <= n <= 45
 *
 */

// problem: https://leetcode.com/problems/climbing-stairs/
// discuss: https://leetcode.com/problems/climbing-stairs/discuss/

#include <iostream>

using namespace std;

// submission codes start here

class Solution {
public:
    int climbStairs(int n) {
        int a = 1;
        int b = 1;

        while (n--) {
            a = (b += a) - a;
        }

        return a;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0070, Example1) {
    Solution solution;

    auto n = 2;

    auto result = 2;

    EXPECT_EQ(solution.climbStairs(n), result);
}

TEST(Problem0070, Example2) {
    Solution solution;

    auto n = 3;

    auto result = 3;

    EXPECT_EQ(solution.climbStairs(n), result);
}

#endif
