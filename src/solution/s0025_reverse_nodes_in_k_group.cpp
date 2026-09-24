/**
 * File              : s0025_reverse_nodes_in_k_group.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-24 19:39:22
 * Last Modified Date: 2026-09-24 21:33:51
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0025] Reverse Nodes in k-Group
 *
 * Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list. k is a positive integer and is less than or
 * equal to the length of the linked list. If the number of nodes is not a
 * multiple of k then left-out nodes, in the end, should remain as it is. You
 * may not alter the values in the list's nodes, only nodes themselves may be
 * changed.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 * Example 2:
 * Input: head = [1,2,3,4,5], k = 3
 * Output: [3,2,1,4,5]
 *
 * Constraints:
 * 	The number of nodes in the list is n.
 * 	1 <= k <= n <= 5000
 * 	0 <= Node.val <= 1000
 *
 * Follow-up: Can you solve the problem in O(1) extra memory space?
 *
 */

// problem: https://leetcode.com/problems/reverse-nodes-in-k-group/
// discuss: https://leetcode.com/problems/reverse-nodes-in-k-group/discuss/

#include <stack>

// Utility headers
#include "../util/linked_list.h"

using namespace std;
using util::ListNode;

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1 || !head) {
            return head;
        }

        stack<ListNode*> stk;
        auto dummy = new ListNode(0);

        dummy->next = head;

        auto left = dummy;

        while (left) {
            auto cnt = k;
            auto right = left->next;
            auto cur = left;

            while (cnt-- && right) {
                stk.push(right);
                right = right->next;
            }

            if ((cnt != -1) && ((!right) || right->next)) {
                break;
            }

            /* First, left->next is the top of stack */

            left->next = stk.top();
            cur = left->next;
            stk.pop();

            while (!stk.empty()) {
                cur->next = stk.top();
                cur = cur->next;
                stk.pop();
            }

            /* Then, the last one point to right */
            cur->next = right;

            /* Change left */
            left = cur;
        }

        return dummy->next;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

// gtest utility headers
#include "../util/linked_list_gtest.h"

TEST(Problem0025, Example1) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto k = 2;

    auto result = util::to_linked_list("[2,1,4,3,5]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, Example2) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto k = 3;

    auto result = util::to_linked_list("[3,2,1,4,5]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, AdditionalCaseSpecialOneGroup) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto k = 1;

    auto result = util::to_linked_list("[1,2,3,4,5]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, AdditionalCaseEmptyList) {
    Solution solution;

    auto head = util::to_linked_list("[]");
    auto k = 3;

    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, AdditionalCaseSpecialAllGroup) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto k = 5;

    auto result = util::to_linked_list("[5,4,3,2,1]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, AdditionalCaseExactMultipleK) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4]");
    auto k = 2;

    auto result = util::to_linked_list("[2,1,4,3]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, AdditionalCaseSingleNode) {
    Solution solution;

    auto head = util::to_linked_list("[1]");
    auto k = 1;

    auto result = util::to_linked_list("[1]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, AdditionalCaseLargeKWithRemainingNodes) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto k = 4;

    auto result = util::to_linked_list("[4,3,2,1,5]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

TEST(Problem0025, AdditionalCaseMultipleFullGroups) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5,6]");
    auto k = 3;

    auto result = util::to_linked_list("[3,2,1,6,5,4]");

    EXPECT_EQ_LINKED_LIST(solution.reverseKGroup(head, k), result);
}

#endif
