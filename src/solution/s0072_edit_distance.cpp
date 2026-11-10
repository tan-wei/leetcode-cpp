/**
 * File              : s0072_edit_distance.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-10 19:30:06
 * Last Modified Date: 2026-11-10 21:23:13
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0072] Edit Distance
 *
 * Given two strings word1 and word2, return the minimum number of operations
 * required to convert word1 to word2. You have the following three operations
 * permitted on a word: Insert a character Delete a character Replace a
 * character
 *
 * Example 1:
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation:
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 * Example 2:
 * Input: word1 = "intention", word2 = "execution"
 * Output: 5
 * Explanation:
 * intention -> inention (remove 't')
 * inention -> enention (replace 'i' with 'e')
 * enention -> exention (replace 'n' with 'x')
 * exention -> exection (replace 'n' with 'c')
 * exection -> execution (insert 'u')
 *
 * Constraints:
 * 	0 <= word1.length, word2.length <= 500
 * 	word1 and word2 consist of lowercase English letters.
 *
 */

// problem: https://leetcode.com/problems/edit-distance/
// discuss: https://leetcode.com/problems/edit-distance/discuss/

#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    int minDistance(string word1, string word2) {
        vector<vector<int>> notebook(
            word1.length(), vector<int>(word2.length(), -1));
        return minDistance(word1, word2, 0, 0, notebook);
    }

private:
    int minDistance(const string& word1, const string& word2, int i, int j,
                    vector<vector<int>>& notebook) {
        if (i == word1.length()) {
            return word2.length() - j;
        }

        if (j == word2.length()) {
            return word1.length() - i;
        }

        if (notebook[i][j] != -1) {
            return notebook[i][j];
        }

        if (word1[i] == word2[j]) {
            int result = minDistance(word1, word2, i + 1, j + 1, notebook);
            notebook[i][j] = result;
            return result;
        } else {
            int insert_distance = minDistance(word1, word2, i, j + 1, notebook);
            int delete_distance = minDistance(word1, word2, i + 1, j, notebook);
            int replace_distance =
                minDistance(word1, word2, i + 1, j + 1, notebook);
            int result =
                min(min(insert_distance, delete_distance), replace_distance) +
                1;
            notebook[i][j] = result;
            return result;
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0072, Example1) {
    Solution solution;

    auto word1 = "horse"s;
    auto word2 = "ros"s;

    auto result = 3;

    EXPECT_EQ(solution.minDistance(word1, word2), result);
}

TEST(Problem0072, Example2) {
    Solution solution;

    auto word1 = "intention"s;
    auto word2 = "execution"s;

    auto result = 5;

    EXPECT_EQ(solution.minDistance(word1, word2), result);
}

#endif
