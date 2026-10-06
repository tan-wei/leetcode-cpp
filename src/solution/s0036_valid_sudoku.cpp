/**
 * File              : s0036_valid_sudoku.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-05 18:56:51
 * Last Modified Date: 2026-10-06 09:18:34
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0036] Valid Sudoku
 *
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
 * validated according to the following rules: Each row must contain the digits
 * 1-9 without repetition. Each column must contain the digits 1-9 without
 * repetition. Each of the nine 3 x 3 sub-boxes of the grid must contain the
 * digits 1-9 without repetition. Note: A Sudoku board (partially filled) could
 * be valid but is not necessarily solvable. Only the filled cells need to be
 * validated according to the mentioned rules.
 *
 * Example 1:
 * Input: board =
 * [["5","3",".",".","7",".",".",".","."]
 * ,["6",".",".","1","9","5",".",".","."]
 * ,[".","9","8",".",".",".",".","6","."]
 * ,["8",".",".",".","6",".",".",".","3"]
 * ,["4",".",".","8",".","3",".",".","1"]
 * ,["7",".",".",".","2",".",".",".","6"]
 * ,[".","6",".",".",".",".","2","8","."]
 * ,[".",".",".","4","1","9",".",".","5"]
 * ,[".",".",".",".","8",".",".","7","9"]]
 * Output: true
 * Example 2:
 * Input: board =
 * [["8","3",".",".","7",".",".",".","."]
 * ,["6",".",".","1","9","5",".",".","."]
 * ,[".","9","8",".",".",".",".","6","."]
 * ,["8",".",".",".","6",".",".",".","3"]
 * ,["4",".",".","8",".","3",".",".","1"]
 * ,["7",".",".",".","2",".",".",".","6"]
 * ,[".","6",".",".",".",".","2","8","."]
 * ,[".",".",".","4","1","9",".",".","5"]
 * ,[".",".",".",".","8",".",".","7","9"]]
 * Output: false
 * Explanation: Same as Example 1, except with the 5 in the top left corner
 * being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it
 * is invalid.
 *
 * Constraints:
 * 	board.length == 9
 * 	board[i].length == 9
 * 	board[i][j] is a digit 1-9 or '.'.
 *
 */

// problem: https://leetcode.com/problems/valid-sudoku/
// discuss: https://leetcode.com/problems/valid-sudoku/discuss/

#include <array>
#include <bitset>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        array<bitset<kBoardSize>, kBoardSize> rows{};
        array<bitset<kBoardSize>, kBoardSize> cols{};
        array<bitset<kBoardSize>, kBoardSize> boxes{};

        for (size_t i = 0; i < kBoardSize; ++i) {
            for (size_t j = 0; j < kBoardSize; ++j) {
                const char ch = board[i][j];
                if (ch == '.') {
                    continue;
                }

                const size_t num = static_cast<size_t>(ch - '1');
                const size_t box_idx =
                    (i / kBoxSize) * kBoxSize + (j / kBoxSize);

                if (rows[i].test(num) ||
                    cols[j].test(num) ||
                    boxes[box_idx].test(num)) {
                    return false;
                }

                rows[i].set(num);
                cols[j].set(num);
                boxes[box_idx].set(num);
            }
        }

        return true;
    }

private:
    static constexpr size_t kBoardSize = 9;
    static constexpr size_t kBoxSize = 3;
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0036, Example1) {
    Solution solution;

    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    auto result = true;

    EXPECT_EQ(solution.isValidSudoku(board), result);
}

TEST(Problem0036, Example2) {
    Solution solution;

    vector<vector<char>> board = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    auto result = false;

    EXPECT_EQ(solution.isValidSudoku(board), result);
}

TEST(Problem0036, AdditionalCaseDuplicateInColumn) {
    Solution solution;

    vector<vector<char>> board = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '.', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    auto result = false;

    EXPECT_EQ(solution.isValidSudoku(board), result);
}

TEST(Problem0036, AdditionalCaseEmptyBoard) {
    Solution solution;

    vector<vector<char>> board(9, vector<char>(9, '.'));

    auto result = true;

    EXPECT_EQ(solution.isValidSudoku(board), result);
}

TEST(Problem0036, AdditionalCaseDuplicateInRow) {
    Solution solution;

    vector<vector<char>> board = {
        {'5', '3', '5', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    auto result = false;

    EXPECT_EQ(solution.isValidSudoku(board), result);
}

#endif
