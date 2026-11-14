/**
 * File              : s0076_minimum_window_substring.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-14 12:10:55
 * Last Modified Date: 2026-11-14 18:19:19
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0076] Minimum Window Substring
 *
 * Given two strings s and t of lengths m and n respectively, return the minimum
 * window substring of s such that every character in t (including duplicates)
 * is included in the window. If there is no such substring, return the empty
 * string "". The testcases will be generated such that the answer is unique.
 *
 * Example 1:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C'
 * from string t.
 * Example 2:
 * Input: s = "a", t = "a"
 * Output: "a"
 * Explanation:
 * The entire string s is the minimum window.
 * Example 3:
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Both 'a's from t must be included in the window.
 * Since the largest window of s only has one 'a', return empty string.
 *
 * Constraints:
 * 	m == s.length
 * 	n == t.length
 * 	1 <= m, n <= 10^5
 * 	s and t consist of uppercase and lowercase English letters.
 *
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 *
 */

// problem: https://leetcode.com/problems/minimum-window-substring/
// discuss: https://leetcode.com/problems/minimum-window-substring/discuss/

#include <limits>
#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // Credit:
    // https://leetcode.com/problems/minimum-window-substring/solutions/26808/here-is-a-10-line-template-that-can-solv-lct0/

    // cppcheck-suppress passedByValue
    string minWindow(string s, string t) {
        vector<int> map(128, 0);

        for (auto c : t) {
            map[c]++;
        }

        int counter = t.size();
        int begin = 0;
        int end = 0;
        int d = numeric_limits<int>::max();
        int head = 0;

        while (end < s.size()) {
            if (map[s[end++]]-- > 0) {
                --counter; // in t
            }
            while (counter == 0) { // valid
                if (end - begin < d) {
                    d = end - (head = begin);
                }
                if (map[s[begin++]]++ == 0) {
                    ++counter; // make it invalid
                }
            }
        }
        return d == numeric_limits<int>::max() ? "" : s.substr(head, d);
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0076, Example1) {
    Solution solution;

    auto s = "ADOBECODEBANC"s;
    auto t = "ABC"s;

    auto result = "BANC"s;

    EXPECT_EQ(solution.minWindow(s, t), result);
}

TEST(Problem0076, Example2) {
    Solution solution;

    auto s = "a"s;
    auto t = "a"s;

    auto result = "a"s;

    EXPECT_EQ(solution.minWindow(s, t), result);
}

TEST(Problem0076, Example3) {
    Solution solution;

    auto s = "a"s;
    auto t = "aa"s;

    auto result = ""s;

    EXPECT_EQ(solution.minWindow(s, t), result);
}

#endif
