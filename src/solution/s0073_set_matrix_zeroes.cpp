/**
 * File              : s0073_set_matrix_zeroes.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-11 19:15:19
 * Last Modified Date: 2026-11-11 20:57:23
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0073] Set Matrix Zeroes
 *
 * Given an m x n integer matrix matrix, if an element is 0, set its entire row
 * and column to 0's. You must do it in place.
 *
 * Example 1:
 * Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
 * Output: [[1,0,1],[0,0,0],[1,0,1]]
 * Example 2:
 * Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
 * Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 *
 * Constraints:
 * 	m == matrix.length
 * 	n == matrix[0].length
 * 	1 <= m, n <= 200
 * 	-2^31 <= matrix[i][j] <= 2^31 - 1
 *
 * Follow up:
 * 	A straightforward solution using O(mn) space is probably a bad idea.
 * 	A simple improvement uses O(m + n) space, but still not the best solution.
 * 	Could you devise a constant space solution?
 *
 */

// problem: https://leetcode.com/problems/set-matrix-zeroes/
// discuss: https://leetcode.com/problems/set-matrix-zeroes/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int col0 = 1;
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int i = 0; i < rows; i++) {
            if (matrix[i][0] == 0) {
                col0 = 0;
            }
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }

        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 1; j--) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
            if (col0 == 0) {
                matrix[i][0] = 0;
            }
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0073, Example1) {
    Solution solution;

    vector<vector<int>> matrix = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

    vector<vector<int>> result = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};

    solution.setZeroes(matrix);

    EXPECT_EQ(matrix, result);
}

TEST(Problem0073, Example2) {
    Solution solution;

    vector<vector<int>> matrix = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};

    vector<vector<int>> result = {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}};

    solution.setZeroes(matrix);

    EXPECT_EQ(matrix, result);
}

#endif
