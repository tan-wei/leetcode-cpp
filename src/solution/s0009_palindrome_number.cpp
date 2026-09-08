/**
 * File              : s0009_palindrome_number.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-08 20:20:28
 * Last Modified Date: 2026-09-08 20:37:34
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0009] Palindrome Number
 *
 * Given an integer x, return true if x is a palindrome, and false otherwise.
 *
 * Example 1:
 * Input: x = 121
 * Output: true
 * Explanation: 121 reads as 121 from left to right and from right to left.
 * Example 2:
 * Input: x = -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it
 * becomes 121-. Therefore it is not a palindrome.
 * Example 3: Input: x = 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 *
 * Constraints:
 * 	-2^31 <= x <= 2^31 - 1
 *
 * Follow up: Could you solve it without converting the integer to a string?
 */

// problem: https://leetcode.com/problems/palindrome-number/
// discuss: https://leetcode.com/problems/palindrome-number/discuss/

#include <iostream>

using namespace std;

// submission codes start here

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x != 0 && x % 10 == 0)) {
            // Special cases
            return false;
        }

        int rev = 0;

        while (rev < x) {
            // Prevent from overflow
            rev = rev * 10 + x % 10;
            x = x / 10;
        }

        if (rev == x || (rev / 10) == x) {
            // Prevent from overflow
            return true;
        } else {
            return false;
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0009, Example1) {
    Solution solution;

    auto x = 121;

    auto result = true;

    EXPECT_EQ(solution.isPalindrome(x), result);
}

TEST(Problem0009, Example2) {
    Solution solution;

    auto x = -121;

    auto result = false;

    EXPECT_EQ(solution.isPalindrome(x), result);
}

TEST(Problem0009, Example3) {
    Solution solution;

    auto x = 10;

    auto result = false;

    EXPECT_EQ(solution.isPalindrome(x), result);
}

TEST(Problem0009, RuntimeErrorOverFlowCase1) {
    Solution solution;

    auto x = 1'234'567'899;

    auto result = false;

    EXPECT_EQ(solution.isPalindrome(x), result);
}

#endif
