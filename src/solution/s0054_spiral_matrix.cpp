/**
 * File              : s0054_spiral_matrix.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-23 18:54:53
 * Last Modified Date: 2026-10-23 20:51:45
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0054] Spiral Matrix
 *
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * Example 1:
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,2,3,6,9,8,7,4,5]
 * Example 2:
 * Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 * Constraints:
 * 	m == matrix.length
 * 	n == matrix[i].length
 * 	1 <= m, n <= 10
 * 	-100 <= matrix[i][j] <= 100
 *
 */

// problem: https://leetcode.com/problems/spiral-matrix/
// discuss: https://leetcode.com/problems/spiral-matrix/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) { // check m, n
        int m = matrix.size();
        int n = matrix[0].size();

        // 4 barrier
        int right = n - 1;
        int down = m - 1;
        int left = 0;
        int up = 0;

        vector<int> result;

        while (true) {
            // left -> right
            for (int j = left; j <= right; j++) {
                result.push_back(matrix[up][j]);
            }
            up++;
            if (up > down) {
                break;
            }

            // up -> down
            for (int i = up; i <= down; i++) {
                result.push_back(matrix[i][right]);
            }
            right--;
            if (right < left) {
                break;
            }

            // right -> left
            for (int j = right; j >= left; j--) {
                result.push_back(matrix[down][j]);
            }
            down--;
            if (down < up) {
                break;
            }

            // down -> up
            for (int i = down; i >= up; i--) {
                result.push_back(matrix[i][left]);
            }
            left++;
            if (left > right) {
                break;
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0054, Example1) {
    Solution solution;

    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    vector<int> result = {1, 2, 3, 6, 9, 8, 7, 4, 5};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, Example2) {
    Solution solution;

    vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    vector<int> result = {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, AdditionalCaseSingleElement) {
    Solution solution;

    vector<vector<int>> matrix = {{5}};

    vector<int> result = {5};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, AdditionalCaseSingleRow) {
    Solution solution;

    vector<vector<int>> matrix = {{1, 2, 3, 4, 5}};

    vector<int> result = {1, 2, 3, 4, 5};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, AdditionalCaseSingleColumn) {
    Solution solution;

    vector<vector<int>> matrix = {{1}, {2}, {3}, {4}};

    vector<int> result = {1, 2, 3, 4};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, AdditionalCaseTwoRowsManyCols) {
    Solution solution;

    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}};

    vector<int> result = {1, 2, 3, 6, 5, 4};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, AdditionalCaseTwoColsManyRows) {
    Solution solution;

    vector<vector<int>> matrix = {{1, 2}, {3, 4}, {5, 6}};

    vector<int> result = {1, 2, 4, 6, 5, 3};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, AdditionalCaseNegativeNumbers) {
    Solution solution;

    vector<vector<int>> matrix = {{-1, -2}, {-3, -4}};

    vector<int> result = {-1, -2, -4, -3};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

TEST(Problem0054, AdditionalCaseTwoByTwo) {
    Solution solution;

    vector<vector<int>> matrix = {{10, 20}, {30, 40}};

    vector<int> result = {10, 20, 40, 30};

    EXPECT_EQ(solution.spiralOrder(matrix), result);
}

#endif
