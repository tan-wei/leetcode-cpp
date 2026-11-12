/**
 * File              : s0074_search_a_2d_matrix.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-12 20:59:40
 * Last Modified Date: 2026-11-12 21:16:34
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0074] Search a 2D Matrix
 *
 * You are given an m x n integer matrix matrix with the following two
 * properties: Each row is sorted in non-decreasing order. The first integer of
 * each row is greater than the last integer of the previous row. Given an
 * integer target, return true if target is in matrix or false otherwise. You
 * must write a solution in O(log(m * n)) time complexity.
 *
 * Example 1:
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
 * Output: true
 * Example 2:
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
 * Output: false
 *
 * Constraints:
 * 	m == matrix.length
 * 	n == matrix[i].length
 * 	1 <= m, n <= 100
 * 	-10^4 <= matrix[i][j], target <= 10^4
 *
 */

// problem: https://leetcode.com/problems/search-a-2d-matrix/
// discuss: https://leetcode.com/problems/search-a-2d-matrix/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int left = 0;
        int right = m * n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int mid_val = matrix[mid / n][mid % n];

            if (mid_val == target) {
                return true;
            } else if (mid_val < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0074, Example1) {
    Solution solution;

    vector<vector<int>> matrix = {
        {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    auto target = 3;

    auto result = true;

    EXPECT_EQ(solution.searchMatrix(matrix, target), result);
}

TEST(Problem0074, Example2) {
    Solution solution;

    vector<vector<int>> matrix = {
        {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    auto target = 13;

    auto result = false;

    EXPECT_EQ(solution.searchMatrix(matrix, target), result);
}

#endif
