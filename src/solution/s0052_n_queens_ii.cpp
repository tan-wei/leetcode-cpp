/**
 * File              : s0052_n_queens_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-21 19:03:58
 * Last Modified Date: 2026-10-21 19:09:21
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0052] N-Queens II
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard
 * such that no two queens attack each other. Given an integer n, return the
 * number of distinct solutions to the n-queens puzzle.
 *
 * Example 1:
 * Input: n = 4
 * Output: 2
 * Explanation: There are two distinct solutions to the 4-queens puzzle as
 * shown.
 * Example 2:
 * Input: n = 1
 * Output: 1
 *
 * Constraints:
 * 	1 <= n <= 9
 *
 */

// problem: https://leetcode.com/problems/n-queens-ii/
// discuss: https://leetcode.com/problems/n-queens-ii/discuss/

#include <iostream>

using namespace std;

// submission codes start here

class Solution {
public:
    int totalNQueens(int n) { return 0; }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0052, Example1) {
    GTEST_SKIP() << "Should be retried, it's a hard and classical one";
    Solution solution;

    auto n = 4;

    auto result = 2;

    EXPECT_EQ(solution.totalNQueens(n), result);
}

TEST(Problem0052, Example2) {
    GTEST_SKIP() << "Should be retried, it's a hard and classical one";
    Solution solution;

    auto n = 1;

    auto result = 1;

    EXPECT_EQ(solution.totalNQueens(n), result);
}

#endif
