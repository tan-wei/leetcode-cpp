/**
 * File              : s0007_reverse_integer.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-06 12:35:52
 * Last Modified Date: 2026-09-06 13:04:21
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0007] Reverse Integer
 *
 * Given a signed 32-bit integer x, return x with its digits reversed. If
 * reversing x causes the value to go outside the signed 32-bit integer range
 * [-2^31, 2^31 - 1], then return 0. Assume the environment does not allow you
 * to store 64-bit integers (signed or unsigned).
 *
 * Example 1:
 * Input: x = 123
 * Output: 321
 * Example 2:
 * Input: x = -123
 * Output: -321
 * Example 3:
 * Input: x = 120
 * Output: 21
 *
 * Constraints:
 * 	-2^31 <= x <= 2^31 - 1
 *
 */

// problem: https://leetcode.com/problems/reverse-integer/
// discuss: https://leetcode.com/problems/reverse-integer/discuss/

#include <algorithm>
#include <limits>

using namespace std;

// submission codes start here

class Solution {
public:
    int reverse(int x) {
        long long result = 0;
        while (x) {
            result = result * 10 + x % 10;
            x = x / 10;
        }

        return result < std::numeric_limits<int>::min() ||
                       result > std::numeric_limits<int>::max()
                   ? 0
                   : result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0007, Example1) {
    Solution solution;

    auto x = 123;

    auto result = 321;

    EXPECT_EQ(solution.reverse(x), result);
}

TEST(Problem0007, Example2) {
    Solution solution;

    auto x = -123;

    auto result = -321;

    EXPECT_EQ(solution.reverse(x), result);
}

TEST(Problem0007, Example3) {
    Solution solution;

    auto x = 120;

    auto result = 21;

    EXPECT_EQ(solution.reverse(x), result);
}

TEST(Problem0007, EdgeCase1) {
    Solution solution;

    auto x = 0;

    auto result = 0;

    EXPECT_EQ(solution.reverse(x), result);
}

TEST(Problem0007, EdgeCase2) {
    Solution solution;

    auto x = 1'563'847'412; // 2'147'483'647 is the max int, 2'147'483'651
                            // greater than this

    auto result = 0;

    EXPECT_EQ(solution.reverse(x), result);
}

TEST(Problem0007, EdgeCase3) {
    Solution solution;

    auto x = -1'563'847'412; // -2'147'483'647 is the min int, -2'147'483'651
                             // less than this

    auto result = 0;

    EXPECT_EQ(solution.reverse(x), result);
}

#endif
