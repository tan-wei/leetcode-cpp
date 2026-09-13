/**
 * File              : s0014_longest_common_prefix.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-13 13:17:05
 * Last Modified Date: 2026-09-13 13:55:43
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0014] Longest Common Prefix
 *
 * Write a function to find the longest common prefix string amongst an array of
 * strings. If there is no common prefix, return an empty string "".
 *
 * Example 1:
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 * Example 2:
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 *
 * Constraints:
 * 	1 <= strs.length <= 200
 * 	0 <= strs[i].length <= 200
 * 	strs[i] consists of only lowercase English letters if it is non-empty.
 *
 */

// problem: https://leetcode.com/problems/longest-common-prefix/
// discuss: https://leetcode.com/problems/longest-common-prefix/discuss/

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    string longestCommonPrefix(vector<string>& strs) {
        string result = "";
        sort(strs.begin(), strs.end());
        string first = strs[0];
        string last = strs[strs.size() - 1];

        for (int i = 0; i < min(first.length(), last.length()); i++) {
            if (first[i] != last[i]) {
                break;
            }
            result += first[i];
        }
        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0014, Example1) {
    Solution solution;

    vector<string> strs = {"flower", "flow", "flight"};

    auto result = "fl"s;

    EXPECT_EQ(solution.longestCommonPrefix(strs), result);
}

TEST(Problem0014, Example2) {
    Solution solution;

    vector<string> strs = {"dog", "racecar", "car"};

    auto result = ""s;

    EXPECT_EQ(solution.longestCommonPrefix(strs), result);
}

#endif
