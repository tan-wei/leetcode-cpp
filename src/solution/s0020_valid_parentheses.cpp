/**
 * File              : s0020_valid_parentheses.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-19 09:13:39
 * Last Modified Date: 2026-09-19 10:47:02
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0020] Valid Parentheses
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid. An input string is valid if:
 * 	Open brackets must be closed by the same type of brackets.
 * 	Open brackets must be closed in the correct order.
 * 	Every close bracket has a corresponding open bracket of the same type.
 *
 * Example 1:
 * Input: s = "()"
 * Output: true
 * Example 2:
 * Input: s = "()[]{}"
 * Output: true
 * Example 3:
 * Input: s = "(]"
 * Output: false
 * Example 4:
 * Input: s = "([])"
 * Output: true
 * Example 5:
 * Input: s = "([)]"
 * Output: false
 *
 * Constraints:
 * 	1 <= s.length <= 10^4
 * 	s consists of parentheses only '()[]{}'.
 *
 */

// problem: https://leetcode.com/problems/valid-parentheses/
// discuss: https://leetcode.com/problems/valid-parentheses/discuss/

#include <stack>
#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    bool isValid(string s) {
        stack<char> temp_stack;

        for (auto c : s) {
            switch (c) {
            case '(':
            case '[':
            case '{': temp_stack.push(c); break;
            case ')':
                if ((!temp_stack.empty()) && (temp_stack.top() == '(')) {
                    temp_stack.pop();
                } else {
                    return false;
                }
                break;
            case ']':
                if ((!temp_stack.empty()) && (temp_stack.top() == '[')) {
                    temp_stack.pop();
                } else {
                    return false;
                }
                break;
            case '}':
                if ((!temp_stack.empty()) && (temp_stack.top() == '{')) {
                    temp_stack.pop();
                } else {
                    return false;
                }
                break;
            default: break;
            }
        }

        return temp_stack.empty();
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0020, Example1) {
    Solution solution;

    auto s = "()"s;

    auto result = true;

    EXPECT_EQ(solution.isValid(s), result);
}

TEST(Problem0020, Example2) {
    Solution solution;

    auto s = "()[]{}"s;

    auto result = true;

    EXPECT_EQ(solution.isValid(s), result);
}

TEST(Problem0020, Example3) {
    Solution solution;

    auto s = "(]"s;

    auto result = false;

    EXPECT_EQ(solution.isValid(s), result);
}

TEST(Problem0020, Example4) {
    Solution solution;

    auto s = "([])"s;

    auto result = true;

    EXPECT_EQ(solution.isValid(s), result);
}

TEST(Problem0020, Example5) {
    Solution solution;

    auto s = "([)]"s;

    auto result = false;

    EXPECT_EQ(solution.isValid(s), result);
}

#endif
