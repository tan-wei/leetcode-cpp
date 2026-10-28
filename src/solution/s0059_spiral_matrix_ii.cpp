/**
 * File              : s0059_spiral_matrix_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-28 20:13:56
 * Last Modified Date: 2026-10-28 20:41:26
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0059] Spiral Matrix II
 *
 * Given a positive integer n, generate an n x n matrix filled with elements
 * from 1 to n^2 in spiral order.
 *
 * Example 1:
 * Input: n = 3
 * Output: [[1,2,3],[8,9,4],[7,6,5]]
 * Example 2:
 * Input: n = 1
 * Output: [[1]]
 *
 * Constraints:
 * 	1 <= n <= 20
 *
 */

// problem: https://leetcode.com/problems/spiral-matrix-ii/
// discuss: https://leetcode.com/problems/spiral-matrix-ii/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        // 4 barrier
        int right = n - 1;
        int down = n - 1;
        int left = 0;
        int up = 0;

        int cur = 0;
        vector<int> v(n, 0);
        vector<vector<int>> result(n, v);

        while (true) {
            // left -> right
            for (int j = left; j <= right; j++) {
                result[up][j] = cur + 1;
                ++cur;
            }

            ++up;

            if (up > down) {
                break;
            }

            // up -> down
            for (int i = up; i <= down; i++) {
                result[i][right] = cur + 1;
                ++cur;
            }

            --right;

            // right -> left
            for (int j = right; j >= left; j--) {
                result[down][j] = cur + 1;
                ++cur;
            }

            --down;

            if (down < up) {
                break;
            }

            // down -> up
            for (int i = down; i >= up; i--) {
                result[i][left] = cur + 1;
                ++cur;
            }

            ++left;
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0059, Example1) {
    Solution solution;

    auto n = 3;

    vector<vector<int>> result = {{1, 2, 3}, {8, 9, 4}, {7, 6, 5}};

    EXPECT_EQ(solution.generateMatrix(n), result);
}

TEST(Problem0059, Example2) {
    Solution solution;

    auto n = 1;

    vector<vector<int>> result = {{1}};

    EXPECT_EQ(solution.generateMatrix(n), result);
}

TEST(Problem0059, AdditionalCaseSizeTwo) {
    Solution solution;

    auto n = 2;

    vector<vector<int>> result = {{1, 2}, {4, 3}};

    EXPECT_EQ(solution.generateMatrix(n), result);
}

TEST(Problem0059, AdditionalCaseSizeFour) {
    Solution solution;

    auto n = 4;

    vector<vector<int>> result = {
        {1, 2, 3, 4}, {12, 13, 14, 5}, {11, 16, 15, 6}, {10, 9, 8, 7}};

    EXPECT_EQ(solution.generateMatrix(n), result);
}

TEST(Problem0059, AdditionalCaseSizeFive) {
    Solution solution;

    auto n = 5;

    vector<vector<int>> result = {
        {1, 2, 3, 4, 5},
        {16, 17, 18, 19, 6},
        {15, 24, 25, 20, 7},
        {14, 23, 22, 21, 8},
        {13, 12, 11, 10, 9}};

    EXPECT_EQ(solution.generateMatrix(n), result);
}

#endif
