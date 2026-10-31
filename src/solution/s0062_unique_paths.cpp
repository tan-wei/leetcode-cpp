/**
 * File              : s0062_unique_paths.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-31 08:56:14
 * Last Modified Date: 2026-10-31 09:07:10
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0062] Unique Paths
 *
 * There is a robot on an m x n grid. The robot is initially located at the
 * top-left corner (i.e., grid[0][0]). The robot tries to move to the
 * bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move
 * either down or right at any point in time. Given the two integers m and n,
 * return the number of possible unique paths that the robot can take to reach
 * the bottom-right corner. The test cases are generated so that the answer will
 * be less than or equal to 2 * 10^9.
 *
 * Example 1:
 * Input: m = 3, n = 7
 * Output: 28
 * Example 2:
 * Input: m = 3, n = 2
 * Output: 3
 * Explanation: From the top-left corner, there are a total of 3 ways to reach
 * the bottom-right corner:
 * 1. Right -> Down -> Down
 * 2. Down -> Down -> Right
 * 3. Down -> Right -> Down
 *
 * Constraints:
 * 	1 <= m, n <= 100
 *
 */

// problem: https://leetcode.com/problems/unique-paths/
// discuss: https://leetcode.com/problems/unique-paths/discuss/

#include <cmath>

using namespace std;

// submission codes start here

class Solution {
public:
    int uniquePaths(int m, int n) {
        int total = m + n - 2;
        int choose = m - 1;
        return static_cast<int>(round(exp(lgamma(total + 1) -
                                          lgamma(choose + 1) -
                                          lgamma(total - choose + 1))));
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0062, Example1) {
    Solution solution;

    auto m = 3;
    auto n = 7;

    auto result = 28;

    EXPECT_EQ(solution.uniquePaths(m, n), result);
}

TEST(Problem0062, Example2) {
    Solution solution;

    auto m = 3;
    auto n = 2;

    auto result = 3;

    EXPECT_EQ(solution.uniquePaths(m, n), result);
}

#endif
