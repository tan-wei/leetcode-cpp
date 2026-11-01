/**
 * File              : s0063_unique_paths_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-01 09:25:54
 * Last Modified Date: 2026-11-01 17:43:06
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0063] Unique Paths II
 *
 * You are given an m x n integer array grid. There is a robot initially located
 * at the top-left corner (i.e., grid[0][0]). The robot tries to move to the
 * bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move
 * either down or right at any point in time. An obstacle and space are marked
 * as 1 or 0 respectively in grid. A path that the robot takes cannot include
 * any square that is an obstacle. Return the number of possible unique paths
 * that the robot can take to reach the bottom-right corner. The testcases are
 * generated so that the answer will be less than or equal to 2 * 10^9.
 *
 * Example 1:
 * Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
 * Output: 2
 * Explanation: There is one obstacle in the middle of the 3x3 grid above.
 * There are two ways to reach the bottom-right corner:
 * 1. Right -> Right -> Down -> Down
 * 2. Down -> Down -> Right -> Right
 * Example 2:
 * Input: obstacleGrid = [[0,1],[0,0]]
 * Output: 1
 *
 * Constraints:
 * 	m == obstacleGrid.length
 * 	n == obstacleGrid[i].length
 * 	1 <= m, n <= 100
 * 	obstacleGrid[i][j] is 0 or 1.
 *
 */

// problem: https://leetcode.com/problems/unique-paths-ii/
// discuss: https://leetcode.com/problems/unique-paths-ii/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                } else {
                    if (i == m - 1 && j == n - 1) {
                        dp[i][j] = 1;
                    } else if (i == m - 1) {
                        dp[i][j] = dp[i][j + 1];
                    } else if (j == n - 1) {
                        dp[i][j] = dp[i + 1][j];
                    } else {
                        dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
                    }
                }
            }
        }

        return dp[0][0];
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0063, Example1) {
    Solution solution;

    vector<vector<int>> obstacleGrid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    auto result = 2;

    EXPECT_EQ(solution.uniquePathsWithObstacles(obstacleGrid), result);
}

TEST(Problem0063, Example2) {
    Solution solution;

    vector<vector<int>> obstacleGrid = {{0, 1}, {0, 0}};

    auto result = 1;

    EXPECT_EQ(solution.uniquePathsWithObstacles(obstacleGrid), result);
}

#endif
