/**
 * File              : s0019_remove_nth_node_from_end_of_list.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-18 20:17:17
 * Last Modified Date: 2026-09-18 21:07:52
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0019] Remove Nth Node From End of List
 *
 * Given the head of a linked list, remove the n^th node from the end of the
 * list and return its head.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 * Example 2:
 * Input: head = [1], n = 1
 * Output: []
 * Example 3:
 * Input: head = [1,2], n = 1
 * Output: [1]
 *
 * Constraints:
 * 	The number of nodes in the list is sz.
 * 	1 <= sz <= 30
 * 	0 <= Node.val <= 100
 * 	1 <= n <= sz
 *
 * Follow up: Could you do this in one pass?
 *
 */

// problem: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
// discuss:
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/discuss/

#include <list>

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto result = new ListNode(0, head);
        auto dummy = result;

        for (int i = 0; i < n; i++) {
            head = head->next;
        }

        while (head != nullptr) {
            head = head->next;
            dummy = dummy->next;
        }

        dummy->next = dummy->next->next;

        return result->next;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

// gtest utility headers
#include "../util/linked_list_gtest.h"

TEST(Problem0019, Example1) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto n = 2;

    auto result = util::to_linked_list("[1,2,3,5]");

    EXPECT_PRED_FORMAT2(list_equal, solution.removeNthFromEnd(head, n), result);
}

TEST(Problem0019, Example2) {
    Solution solution;

    auto head = util::to_linked_list("[1]");
    auto n = 1;

    auto result = util::to_linked_list("[]");

    EXPECT_PRED_FORMAT2(list_equal, solution.removeNthFromEnd(head, n), result);
}

TEST(Problem0019, Example3) {
    Solution solution;

    auto head = util::to_linked_list("[1,2]");
    auto n = 1;

    auto result = util::to_linked_list("[1]");

    EXPECT_PRED_FORMAT2(list_equal, solution.removeNthFromEnd(head, n), result);
}

#endif
