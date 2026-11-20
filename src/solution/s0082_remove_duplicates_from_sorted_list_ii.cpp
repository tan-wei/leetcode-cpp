/**
 * File              : s0082_remove_duplicates_from_sorted_list_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-20 21:11:13
 * Last Modified Date: 2026-11-20 21:39:26
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0082] Remove Duplicates from Sorted List II
 *
 * You are given the head of a sorted linked list.
 * Delete all nodes that have duplicate numbers, leaving only distinct numbers
 * from the original list. Return the linked list sorted as well.
 *
 * Example 1:
 * Input: head = [1,2,3,3,4,4,5]
 * Output: [1,2,5]
 * Example 2:
 * Input: head = [1,1,1,2,3]
 * Output: [2,3]
 *
 * Constraints:
 * 	The number of nodes in the list is in the range [0, 300].
 * 	-100 <= Node.val <= 100
 * 	The list is guaranteed to be sorted in ascending order.
 *
 */

// problem: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// discuss:
// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/discuss/

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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode dummy(0);
        dummy.next = head;

        ListNode* cur = head;
        ListNode* former_node = &dummy;
        ListNode* remain_former_node = &dummy;

        bool first = true;
        int former_val = 0;
        bool removed = false;

        while (cur) {
            if (first == false && former_val == cur->val) {
                remain_former_node->next = cur->next;
                removed = true;

            } else if (first == true) {
                first = false;
                former_node = cur;
                former_val = cur->val;
            } else {
                former_val = cur->val;
                if (removed == false) {
                    // former node is not removed, remian_former_node should
                    // change
                    remain_former_node = former_node;
                } else {
                    // former node is removed, do not change remian_former_node
                    removed = false;
                }

                former_node = cur;
            }
            cur = cur->next;
        }

        return dummy.next;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

// gtest utility headers
#include "../util/linked_list_gtest.h"

TEST(Problem0082, Example1) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,3,4,4,5]");

    auto result = util::to_linked_list("[1,2,5]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, Example2) {
    Solution solution;

    auto head = util::to_linked_list("[1,1,1,2,3]");

    auto result = util::to_linked_list("[2,3]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseEmptyList) {
    Solution solution;

    auto head = util::to_linked_list("[]");
    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseSingleNode) {
    Solution solution;

    auto head = util::to_linked_list("[5]");
    auto result = util::to_linked_list("[5]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseAllDuplicate) {
    Solution solution;

    auto head = util::to_linked_list("[2,2,2]");
    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseDuplicateAtTail) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,4,4]");
    auto result = util::to_linked_list("[1,2]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseTwoSeparateDuplicateGroup) {
    Solution solution;

    auto head = util::to_linked_list("[1,1,2,3,3]");
    auto result = util::to_linked_list("[2]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseTwoSameNode) {
    Solution solution;

    auto head = util::to_linked_list("[3,3]");
    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseTwoDiffNode) {
    Solution solution;

    auto head = util::to_linked_list("[3,4]");
    auto result = util::to_linked_list("[3,4]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseNegativeValue) {
    Solution solution;

    auto head = util::to_linked_list("[-3,-3,-2,-1,-1,0]");
    auto result = util::to_linked_list("[-2,0]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0082, AdditionalCaseConsecutiveDuplicateBlock) {
    Solution solution;

    auto head = util::to_linked_list("[1,1,2,2,3]");
    auto result = util::to_linked_list("[3]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

#endif
