/**
 * File              : s0079_word_search.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-17 22:38:50
 * Last Modified Date: 2026-11-17 23:30:48
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0079] Word Search
 *
 * Given an m x n grid of characters board and a string word, return true if
 * word exists in the grid. The word can be constructed from letters of
 * sequentially adjacent cells, where adjacent cells are horizontally or
 * vertically neighboring. The same letter cell may not be used more than once.
 *
 * Example 1:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
 * word = "ABCCED"
 * Output: true
 * Example 2:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
 * word = "SEE"
 * Output: true
 * Example 3:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
 * word = "ABCB"
 * Output: false
 *
 * Constraints:
 * 	m == board.length
 * 	n = board[i].length
 * 	1 <= m, n <= 6
 * 	1 <= word.length <= 15
 * 	board and word consists of only lowercase and uppercase English letters.
 *
 * Follow up: Could you use search pruning to make your solution faster with a
 * larger board?
 *
 */

// problem: https://leetcode.com/problems/word-search/
// discuss: https://leetcode.com/problems/word-search/discuss/

#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        if (word.length() > m * n) {
            return false;
        }

        vector<vector<int>> mark(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (exist(board, word, i, j, mark)) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    bool exist(vector<vector<char>>& board, const string& word, int i, int j,
               vector<vector<int>>& mark) {
        int m = board.size();
        int n = board[0].size();

        if (mark[i][j] == 0 && word[0] == board[i][j]) {
            if (word.length() == 1) {
                return true;
            }
            bool found = false;
            mark[i][j] = 1;
            // find left
            if (j > 0) {
                found = exist(board, word.substr(1), i, j - 1, mark);
            }
            // find right
            if (found == false && j + 1 < n) {
                found = exist(board, word.substr(1), i, j + 1, mark);
            }
            // find up
            if (found == false && i > 0) {
                found = exist(board, word.substr(1), i - 1, j, mark);
            }
            // find down
            if (found == false && i + 1 < m) {
                found = exist(board, word.substr(1), i + 1, j, mark);
            }

            if (!found) {
                mark[i][j] = 0;
            }

            return found;
        } else {
            return false;
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0079, Example1) {
    Solution solution;

    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    auto word = "ABCCED"s;

    auto result = true;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, Example2) {
    Solution solution;

    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    auto word = "SEE"s;

    auto result = true;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, Example3) {
    Solution solution;

    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    auto word = "ABCB"s;

    auto result = false;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, AdditionalCaseSingleCellMatch) {
    Solution solution;

    vector<vector<char>> board = {{'A'}};
    auto word = "A"s;

    auto result = true;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, AdditionalCaseSingleCellMismatch) {
    Solution solution;

    vector<vector<char>> board = {{'A'}};
    auto word = "B"s;

    auto result = false;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, AdditionalCaseWordTooLong) {
    Solution solution;

    vector<vector<char>> board = {{'A', 'B'}, {'C', 'D'}};
    auto word = "ABCDE"s;

    auto result = false;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, AdditionalCaseSingleRowBoard) {
    Solution solution;

    vector<vector<char>> board = {{'A', 'B', 'C', 'D'}};
    auto word = "CBA"s;

    auto result = true;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, AdditionalCaseSingleColBoard) {
    Solution solution;

    vector<vector<char>> board = {{'A'}, {'B'}, {'C'}, {'D'}};
    auto word = "DCB"s;

    auto result = true;

    EXPECT_EQ(solution.exist(board, word), result);
}

TEST(Problem0079, AdditionalCaseBacktrackingResetTest) {
    Solution solution;

    vector<vector<char>> board = {
        {'C', 'A', 'A'}, {'A', 'A', 'A'}, {'B', 'C', 'D'}};

    auto word = "AAB"s;

    auto result = true;

    EXPECT_EQ(solution.exist(board, word), result);
}

#endif
