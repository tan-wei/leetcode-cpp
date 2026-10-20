/**
 * File              : s0051_n_queens.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-20 20:03:29
 * Last Modified Date: 2026-10-20 20:13:10
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0051] N-Queens
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard
 * such that no two queens attack each other. Given an integer n, return all
 * distinct solutions to the n-queens puzzle. You may return the answer in any
 * order. Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space,
 * respectively.
 *
 * Example 1:
 * Input: n = 4
 * Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * Explanation: There exist two distinct solutions to the 4-queens puzzle as
 * shown above Example 2: Input: n = 1 Output: [["Q"]]
 *
 * Constraints:
 * 	1 <= n <= 9
 *
 */

// problem: https://leetcode.com/problems/n-queens/
// discuss: https://leetcode.com/problems/n-queens/discuss/

#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) { return {}; }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0051, Example1) {
    GTEST_SKIP() << "Should be retried, it's a hard and classical one";
    Solution solution;

    auto n = 4;

    vector<vector<string>> result = {
        {".Q..", "...Q", "Q...", "..Q."}, {"..Q.", "Q...", "...Q", ".Q.."}};

    EXPECT_THAT(solution.solveNQueens(n),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0051, Example2) {
    GTEST_SKIP() << "Should be retried, it's a hard and classical one";
    Solution solution;

    auto n = 1;

    vector<vector<string>> result = {{"Q"}};

    EXPECT_THAT(solution.solveNQueens(n),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
