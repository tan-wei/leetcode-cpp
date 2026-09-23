/**
 * File              : s0024_swap_nodes_in_pairs.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-23 21:44:29
 * Last Modified Date: 2026-09-23 22:11:18
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0024] Swap Nodes in Pairs
 *
 * Given a linked list, swap every two adjacent nodes and return its head. You
 * must solve the problem without modifying the values in the list's nodes
 * (i.e., only nodes themselves may be changed.)
 *
 * Example 1:
 * Input: head = [1,2,3,4]
 * Output: [2,1,4,3]
 * Explanation:
 * Example 2:
 * Input: head = []
 * Output: []
 * Example 3:
 * Input: head = [1]
 * Output: [1]
 * Example 4:
 * Input: head = [1,2,3]
 * Output: [2,1,3]
 *
 * Constraints:
 * 	The number of nodes in the list is in the range [0, 100].
 * 	0 <= Node.val <= 100
 *
 */

// problem: https://leetcode.com/problems/swap-nodes-in-pairs/
// discuss: https://leetcode.com/problems/swap-nodes-in-pairs/discuss/

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
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        auto dummy = new ListNode(0);
        dummy->next = head;

        auto left_left = dummy;
        auto left = head;
        auto right = head->next;
        auto right_right = right->next;

        while (true) {
            left_left->next = right;
            right->next = left;
            left->next = right_right;

            left_left = left;
            left = right_right;

            if (left) {
                right = left->next;
                if (right) {
                    right_right = right->next;
                } else {
                    return dummy->next;
                }
            } else {
                return dummy->next;
            }
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

// gtest utility headers
#include "../util/linked_list_gtest.h"

TEST(Problem0024, Example1) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4]");

    auto result = util::to_linked_list("[2,1,4,3]");

    EXPECT_EQ_LINKED_LIST(solution.swapPairs(head), result);
}

TEST(Problem0024, Example2) {
    Solution solution;

    auto head = util::to_linked_list("[]");

    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.swapPairs(head), result);
}

TEST(Problem0024, Example3) {
    Solution solution;

    auto head = util::to_linked_list("[1]");

    auto result = util::to_linked_list("[1]");

    EXPECT_EQ_LINKED_LIST(solution.swapPairs(head), result);
}

TEST(Problem0024, Example4) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3]");

    auto result = util::to_linked_list("[2,1,3]");

    EXPECT_EQ_LINKED_LIST(solution.swapPairs(head), result);
}

#endif
