/**
 * File              : s0085_maximal_rectangle.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-23 18:41:49
 * Last Modified Date: 2026-11-23 20:03:06
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0085] Maximal Rectangle
 *
 * Given a rows x cols binary matrix filled with 0's and 1's, find the largest
 * rectangle containing only 1's and return its area.
 *
 * Example 1:
 * Input: matrix =
 * [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
 * Output: 6
 * Explanation:
 * The maximal rectangle is shown in the above picture.
 * Example 2:
 * Input: matrix = [["0"]]
 * Output: 0
 * Example 3:
 * Input: matrix = [["1"]]
 * Output: 1
 *
 * Constraints:
 * 	rows == matrix.length
 * 	cols == matrix[i].length
 * 	1 <= rows, cols <= 200
 * 	matrix[i][j] is '0' or '1'.
 *
 */

// problem: https://leetcode.com/problems/maximal-rectangle/
// discuss: https://leetcode.com/problems/maximal-rectangle/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        int result = 0;
        vector<int> hist(n, 0);
        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (matrix[row][col] == '0') {
                    hist[col] = 0;
                } else {
                    hist[col]++;
                }
            }

            int max_area_row = largestRectangleArea(hist);
            if (max_area_row > result) {
                result = max_area_row;
            }
        }

        return result;
    }

private:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        heights.push_back(0);
        vector<int> index;

        for (int i = 0; i < heights.size(); i++) {
            while (index.size() > 0 && heights[index.back()] >= heights[i]) {
                int h = heights[index.back()];
                index.pop_back();

                int sidx = index.size() > 0 ? index.back() : -1;
                if (h * (i - sidx - 1) > result) {
                    result = h * (i - sidx - 1);
                }
            }
            index.push_back(i);
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0085, Example1) {
    Solution solution;

    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}};

    auto result = 6;

    EXPECT_EQ(solution.maximalRectangle(matrix), result);
}

TEST(Problem0085, Example2) {
    Solution solution;

    vector<vector<char>> matrix = {{'0'}};

    auto result = 0;

    EXPECT_EQ(solution.maximalRectangle(matrix), result);
}

TEST(Problem0085, Example3) {
    Solution solution;

    vector<vector<char>> matrix = {{'1'}};

    auto result = 1;

    EXPECT_EQ(solution.maximalRectangle(matrix), result);
}

#endif
