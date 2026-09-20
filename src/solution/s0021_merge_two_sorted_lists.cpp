/**
 * File              : s0021_merge_two_sorted_lists.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-20 08:21:38
 * Last Modified Date: 2026-09-20 08:34:26
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0021] Merge Two Sorted Lists
 *
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists into one sorted list. The list should be made by splicing
 * together the nodes of the first two lists. Return the head of the merged
 * linked list.
 *
 * Example 1:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 * Example 2:
 * Input: list1 = [], list2 = []
 * Output: []
 * Example 3:
 * Input: list1 = [], list2 = [0]
 * Output: [0]
 *
 * Constraints:
 * 	The number of nodes in both lists is in the range [0, 50].
 * 	-100 <= Node.val <= 100
 * 	Both list1 and list2 are sorted in non-decreasing order.
 *
 */

// problem: https://leetcode.com/problems/merge-two-sorted-lists/
// discuss: https://leetcode.com/problems/merge-two-sorted-lists/discuss/

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) {
            return list2;
        }

        if (!list2) {
            return list1;
        }

        auto cur_l1 = list1;
        auto cur_l2 = list2;
        auto dummy = new ListNode(0);
        auto cur = dummy;

        while (cur_l1 && cur_l2) {
            if (cur_l1->val < cur_l2->val) {
                cur->next = new ListNode(cur_l1->val);
                cur_l1 = cur_l1->next;
            } else {
                cur->next = new ListNode(cur_l2->val);
                cur_l2 = cur_l2->next;
            }
            cur = cur->next;
        }

        while (cur_l1) {
            cur->next = new ListNode(cur_l1->val);
            cur_l1 = cur_l1->next;
            cur = cur->next;
        }

        while (cur_l2) {
            cur->next = new ListNode(cur_l2->val);
            cur_l2 = cur_l2->next;
            cur = cur->next;
        }

        return dummy->next;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

// gtest utility headers
#include "../util/linked_list_gtest.h"

TEST(Problem0021, Example1) {
    Solution solution;

    auto list1 = util::to_linked_list("[1,2,4]");
    auto list2 = util::to_linked_list("[1,3,4]");

    auto result = util::to_linked_list("[1,1,2,3,4,4]");

    EXPECT_PRED_FORMAT2(list_equal, solution.mergeTwoLists(list1, list2),
                        result);
}

TEST(Problem0021, Example2) {
    Solution solution;

    auto list1 = util::to_linked_list("[]");
    auto list2 = util::to_linked_list("[]");

    auto result = util::to_linked_list("[]");

    EXPECT_PRED_FORMAT2(list_equal, solution.mergeTwoLists(list1, list2),
                        result);
}

TEST(Problem0021, Example3) {
    Solution solution;

    auto list1 = util::to_linked_list("[]");
    auto list2 = util::to_linked_list("[0]");

    auto result = util::to_linked_list("[0]");

    EXPECT_PRED_FORMAT2(list_equal, solution.mergeTwoLists(list1, list2),
                        result);
}

TEST(Problem0021, AddtionalCase1) {
    Solution solution;

    auto list1 = util::to_linked_list("[0]");
    auto list2 = util::to_linked_list("[]");

    auto result = util::to_linked_list("[0]");

    EXPECT_PRED_FORMAT2(list_equal, solution.mergeTwoLists(list1, list2),
                        result);
}

#endif
