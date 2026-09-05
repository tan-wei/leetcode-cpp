/**
 * File              : s0006_zigzag_conversion.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-05 15:25:47
 * Last Modified Date: 2026-09-05 16:21:51
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0006] Zigzag Conversion
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility) P   A   H   N A P L S I I G Y   I   R And then read line
 * by line: "PAHNAPLSIIGYIR" Write the code that will take a string and make
 * this conversion given a number of rows: string convert(string s, int
 * numRows);
 *
 * Example 1:
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 * Example 2:
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 * Explanation:
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 * Example 3:
 * Input: s = "A", numRows = 1
 * Output: "A"
 *
 * Constraints:
 * 	1 <= s.length <= 1000
 * 	s consists of English letters (lower-case and upper-case), ',' and '.'.
 * 	1 <= numRows <= 1000
 *
 */

// problem: https://leetcode.com/problems/zigzag-conversion/
// discuss: https://leetcode.com/problems/zigzag-conversion/discuss/

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }

        vector<string> rows(min(numRows, static_cast<int>(s.size())));
        int currentRow = 0;
        bool goingDown = false;

        for (auto c : s) {
            rows[currentRow] += c;

            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown;
            }

            currentRow += goingDown ? 1 : -1;
        }

        string result;
        for (const string& row : rows) {
            result += row;
        }
        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0006, Example1) {
    Solution solution;

    auto s = "PAYPALISHIRING"s;
    auto numRows = 3;

    auto result = "PAHNAPLSIIGYIR"s;

    EXPECT_EQ(solution.convert(s, numRows), result);
}

#endif
