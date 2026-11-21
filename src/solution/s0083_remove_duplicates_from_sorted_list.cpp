/**
 * File              : s0083_remove_duplicates_from_sorted_list.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-21 11:42:18
 * Last Modified Date: 2026-11-21 18:40:55
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0083] Remove Duplicates from Sorted List
 *
 * Given the head of a sorted linked list, delete all duplicates such that each
 * element appears only once. Return the linked list sorted as well.
 *
 * Example 1:
 * Input: head = [1,1,2]
 * Output: [1,2]
 * Example 2:
 * Input: head = [1,1,2,3,3]
 * Output: [1,2,3]
 *
 * Constraints:
 * 	The number of nodes in the list is in the range [0, 300].
 * 	-100 <= Node.val <= 100
 * 	The list is guaranteed to be sorted in ascending order.
 *
 */

// problem: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
// discuss:
// https://leetcode.com/problems/remove-duplicates-from-sorted-list/discuss/

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
        bool first = true;
        int former_val = 0;

        while (cur) {
            if (first == false && former_val == cur->val) {
                former_node->next = cur->next;
            } else if (first == true) {
                first = false;
                former_val = cur->val;
                former_node = cur;
            } else {
                former_val = cur->val;
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

TEST(Problem0083, Example1) {
    Solution solution;

    auto head = util::to_linked_list("[1,1,2]");

    auto result = util::to_linked_list("[1,2]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0083, Example2) {
    Solution solution;

    auto head = util::to_linked_list("[1,1,2,3,3]");

    auto result = util::to_linked_list("[1,2,3]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0083, AdditionalCaseEmptyList) {
    Solution solution;

    auto head = util::to_linked_list("[]");
    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0083, AdditionalCaseSingleNode) {
    Solution solution;

    auto head = util::to_linked_list("[5]");
    auto result = util::to_linked_list("[5]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0083, AdditionalCaseAllDuplicate) {
    Solution solution;

    auto head = util::to_linked_list("[2,2,2,2]");
    auto result = util::to_linked_list("[2]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0083, AdditionalCaseNoDuplicate) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto result = util::to_linked_list("[1,2,3,4,5]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0083, AdditionalCaseNegativeValue) {
    Solution solution;

    auto head = util::to_linked_list("[-3,-3,-2,-1,-1,-1]");
    auto result = util::to_linked_list("[-3,-2,-1]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

TEST(Problem0083, AdditionalCaseDuplicateAtTail) {
    Solution solution;

    auto head = util::to_linked_list("[0,1,1]");
    auto result = util::to_linked_list("[0,1]");

    EXPECT_EQ_LINKED_LIST(solution.deleteDuplicates(head), result);
}

#endif
