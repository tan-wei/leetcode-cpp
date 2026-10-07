/**
 * File              : s0038_count_and_say.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-07 20:49:32
 * Last Modified Date: 2026-10-07 22:18:09
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0038] Count and Say
 *
 * The count-and-say sequence is a sequence of digit strings defined by the
 * recursive formula: countAndSay(1) = "1" countAndSay(n) is the run-length
 * encoding of countAndSay(n - 1). Run-length encoding (RLE) is a string
 * compression method that works by replacing each maximal group of consecutive
 * identical characters with the concatenation of the length of the group
 * followed by the character itself. For example, to compress the string
 * "3322251" we replace "33" with "23", replace "222" with "32", replace "5"
 * with "15", and replace "1" with "11". Thus the compressed string becomes
 * "23321511". Given a positive integer n, return the n^th element of the
 * count-and-say sequence.
 *
 * Example 1:
 * Input: n = 4
 * Output: "1211"
 * Explanation:
 * countAndSay(1) = "1"
 * countAndSay(2) = RLE of "1" = "11"
 * countAndSay(3) = RLE of "11" = "21"
 * countAndSay(4) = RLE of "21" = "1211"
 * Example 2:
 * Input: n = 1
 * Output: "1"
 * Explanation:
 * This is the base case.
 *
 * Constraints:
 * 	1 <= n <= 30
 *
 * Follow up: Could you solve it iteratively?
 */

// problem: https://leetcode.com/problems/count-and-say/
// discuss: https://leetcode.com/problems/count-and-say/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) {
            return "1";
        }

        string curr = "1";

        for (int step = 1; step < n; ++step) {
            string next;
            next.reserve(curr.size() * 2);

            const size_t len = curr.size();
            for (size_t i = 0; i < len;) {
                size_t j = i;
                while (j < len && curr[j] == curr[i]) {
                    ++j;
                }

                const size_t count = j - i;
                next.push_back(static_cast<char>('0' + count));
                next.push_back(curr[i]);

                i = j;
            }

            curr = std::move(next);
        }

        return curr;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0038, Example1) {
    Solution solution;

    auto n = 4;

    auto result = "1211"s;

    EXPECT_EQ(solution.countAndSay(n), result);
}

TEST(Problem0038, Example2) {
    Solution solution;

    auto n = 1;

    auto result = "1"s;

    EXPECT_EQ(solution.countAndSay(n), result);
}

TEST(Problem0038, AdditionalCaseWithSmallNumber) {
    Solution solution;

    auto n = 5;

    auto result = "111221"s;

    EXPECT_EQ(solution.countAndSay(n), result);
}

#endif
