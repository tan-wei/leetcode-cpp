/**
 * File              : s0037_sudoku_solver.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-06 19:31:13
 * Last Modified Date: 2026-10-06 20:01:34
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0037] Sudoku Solver
 *
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * A sudoku solution must satisfy all of the following rules:
 * 	Each of the digits 1-9 must occur exactly once in each row.
 * 	Each of the digits 1-9 must occur exactly once in each column.
 * 	Each of the digits 1-9 must occur exactly once in each of the 9 3x3
 * sub-boxes of the grid. The '.' character indicates empty cells.
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
 * Output:
 * [["5","3","4","6","7","8","9","1","2"]
 * ,["6","7","2","1","9","5","3","4","8"]
 * ,["1","9","8","3","4","2","5","6","7"]
 * ,["8","5","9","7","6","1","4","2","3"]
 * ,["4","2","6","8","5","3","7","9","1"]
 * ,["7","1","3","9","2","4","8","5","6"]
 * ,["9","6","1","5","3","7","2","8","4"]
 * ,["2","8","7","4","1","9","6","3","5"]
 * ,["3","4","5","2","8","6","1","7","9"]]
 * Explanation: The input board is shown above and the only valid solution is
 * shown below:
 *
 * Constraints:
 * 	board.length == 9
 * 	board[i].length == 9
 * 	board[i][j] is a digit or '.'.
 * 	It is guaranteed that the input board has only one solution.
 *
 */

// problem: https://leetcode.com/problems/sudoku-solver/
// discuss: https://leetcode.com/problems/sudoku-solver/discuss/

#include <array>
#include <bitset>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solveSudokuDfsHelper(board, 0, 0);
    }

private:
    static constexpr size_t kBoardSize = 9;
    static constexpr size_t kSubBoxSize = 3;

    bool checkNumInLocation(const vector<vector<char>>& board, size_t row,
                            size_t col, char c) {
        // row & column check
        for (size_t i = 0; i < kBoardSize; ++i) {
            if (board[row][i] == c || board[i][col] == c) {
                return false;
            }
        }

        // subbox check
        const size_t box_row = (row / kSubBoxSize) * kSubBoxSize;
        const size_t box_col = (col / kSubBoxSize) * kSubBoxSize;

        for (size_t r = box_row; r < box_row + kSubBoxSize; ++r) {
            for (size_t c_idx = box_col; c_idx < box_col + kSubBoxSize;
                 ++c_idx) {
                if (board[r][c_idx] == c) {
                    return false;
                }
            }
        }

        return true;
    }

    bool solveSudokuDfsHelper(vector<vector<char>>& board, size_t row,
                              size_t col) {
        if (row == kBoardSize) {
            return true;
        }

        const size_t next_row = (col == kBoardSize - 1) ? row + 1 : row;
        const size_t next_col = (col == kBoardSize - 1) ? 0 : col + 1;

        if (board[row][col] != '.') {
            return solveSudokuDfsHelper(board, next_row, next_col);
        }

        for (char ch = '1'; ch <= '9'; ++ch) {
            if (checkNumInLocation(board, row, col, ch)) {
                board[row][col] = ch;
                if (solveSudokuDfsHelper(board, next_row, next_col)) {
                    return true;
                }
                board[row][col] = '.';
            }
        }

        return false;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0037, Example1) {
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

    vector<vector<char>> result = {
        {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
        {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
        {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
        {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
        {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
        {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
        {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
        {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
        {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    solution.solveSudoku(board);

    EXPECT_EQ(board, result);
}

TEST(Problem0037, AdditionalCaseAlmostComplete) {
    Solution solution;

    vector<vector<char>> board = {
        {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
        {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
        {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
        {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
        {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
        {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
        {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
        {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
        {'3', '4', '5', '2', '8', '6', '1', '7', '.'}};

    const vector<vector<char>> result = {
        {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
        {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
        {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
        {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
        {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
        {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
        {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
        {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
        {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    solution.solveSudoku(board);

    EXPECT_EQ(board, result);
}

TEST(Problem0037, AdditionalCaseBacktrackingPressure) {
    Solution solution;

    vector<vector<char>> board = {
        {'1', '.', '.', '.', '.', '7', '.', '.', '.'},
        {'.', '2', '.', '.', '.', '.', '8', '.', '.'},
        {'.', '.', '3', '.', '.', '.', '.', '6', '.'},
        {'.', '.', '.', '4', '.', '.', '.', '.', '5'},
        {'.', '.', '.', '.', '5', '.', '.', '.', '.'},
        {'8', '.', '.', '.', '.', '6', '.', '.', '.'},
        {'.', '7', '.', '.', '.', '.', '4', '.', '.'},
        {'.', '.', '9', '.', '.', '.', '.', '1', '.'},
        {'.', '.', '.', '2', '.', '.', '.', '.', '3'}};

    vector<vector<char>> result = {
        {'1', '4', '5', '6', '8', '7', '2', '3', '9'},
        {'6', '2', '7', '1', '3', '9', '8', '5', '4'},
        {'9', '8', '3', '5', '2', '4', '1', '6', '7'},
        {'2', '9', '6', '4', '1', '3', '7', '8', '5'},
        {'7', '3', '1', '8', '5', '2', '9', '4', '6'},
        {'8', '5', '4', '9', '7', '6', '3', '2', '1'},
        {'5', '7', '2', '3', '6', '1', '4', '9', '8'},
        {'3', '6', '9', '7', '4', '8', '5', '1', '2'},
        {'4', '1', '8', '2', '9', '5', '6', '7', '3'}};

    solution.solveSudoku(board);

    EXPECT_EQ(board, result);
}

#endif
