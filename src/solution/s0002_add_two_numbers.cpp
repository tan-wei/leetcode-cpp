/**
 * File              : s0002_add_two_numbers.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-01 19:58:40
 * Last Modified Date: 2026-09-02 11:55:00
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0002] Add Two Numbers
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order, and each of their nodes
 * contains a single digit. Add the two numbers and return the sum as a linked
 * list. You may assume the two numbers do not contain any leading zero, except
 * the number 0 itself.
 *
 * Example 1:
 * <img alt=""
 * src="https://assets.leetcode.com/uploads/2020/10/02/addtwonumber1.jpg"
 * style="width: 483px; height: 342px;" /> Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807.
 * Example 2:
 * Input: l1 = [0], l2 = [0]
 * Output: [0]
 * Example 3:
 * Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * Output: [8,9,9,9,0,0,0,1]
 *
 * Constraints:
 * 	The number of nodes in each linked list is in the range [1, 100].
 * 	0 <= Node.val <= 9
 * 	It is guaranteed that the list represents a number that does not have
 * leading zeros.
 *
 */

// problem: https://leetcode.com/problems/add-two-numbers/
// discuss: https://leetcode.com/problems/add-two-numbers/discuss/

#include "../util/linked_list.h"

#include <list>
#include <memory>

using namespace std;
using util::ListNode;
using util::to_linked_list;
using util::to_string;
using util::to_vec;

#if defined(ENABLE_GTEST)
#include "../util/linked_list_gtest.h"
#endif

// submission codes start here

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {
        return nullptr;
    }
 *     ListNode(int x) : val(x), next(nullptr) {
        return nullptr;
    }
 *     ListNode(int x, ListNode *next) : val(x), next(next) {
        return nullptr;
    }
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto header = std::make_unique<ListNode>(0);
        ListNode* r = header.get();
        bool carry = false;

        while (l1 || l2 || carry) {
            int sum = 0;
            if (l1) {
                sum += l1->val;
            }
            if (l2) {
                sum += l2->val;
            }
            if (carry) {
                ++sum;
            }

            if (sum >= 10) {
                carry = true;
                r->next = new ListNode(sum % 10);
            } else {
                carry = false;
                r->next = new ListNode(sum);
            }

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
            r = r->next;
        }

        return header->next;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)

TEST(Problem0002, Example1) {
    Solution solution;

    auto l1 = to_linked_list("[2,4,3]");
    auto l2 = to_linked_list("[5,6,4]");
    auto expected = to_linked_list("[7,0,8]");

    auto* result = solution.addTwoNumbers(l1, l2);
    EXPECT_PRED_FORMAT2(list_equal, result, expected);
}

TEST(Problem0002, Example2) {
    Solution solution;

    auto l1 = to_linked_list("[0]");
    auto l2 = to_linked_list("[0]");
    auto expected = to_linked_list("[0]");

    auto* result = solution.addTwoNumbers(l1, l2);
    EXPECT_PRED_FORMAT2(list_equal, result, expected);
}

TEST(Problem0002, Example3) {
    Solution solution;

    auto l1 = to_linked_list("[9,9,9,9,9,9,9]");
    auto l2 = to_linked_list("[9,9,9,9]");
    auto expected = to_linked_list("[8,9,9,9,0,0,0,1]");

    auto* result = solution.addTwoNumbers(l1, l2);
    EXPECT_PRED_FORMAT2(list_equal, result, expected);
}

#endif
