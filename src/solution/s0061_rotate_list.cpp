/**
 * File              : s0061_rotate_list.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-30 22:18:38
 * Last Modified Date: 2026-10-30 22:32:24
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0061] Rotate List
 *
 * Given the head of a linked list, rotate the list to the right by k places.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [4,5,1,2,3]
 * Example 2:
 * Input: head = [0,1,2], k = 4
 * Output: [2,0,1]
 *
 * Constraints:
 * 	The number of nodes in the list is in the range [0, 500].
 * 	-100 <= Node.val <= 100
 * 	0 <= k <= 2 * 10^9
 *
 */

// problem: https://leetcode.com/problems/rotate-list/
// discuss: https://leetcode.com/problems/rotate-list/discuss/

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || k == 0) {
            return head;
        }

        ListNode dummy(0);
        dummy.next = head;
        ListNode* cur = &dummy;
        int list_size = 0;

        while (cur->next) {
            ++list_size;
            cur = cur->next;
        }

        ListNode* last_node = cur;

        k = k % list_size;

        if (!k) {
            // no need to change
            return dummy.next;
        }

        // find the last (k+1)-th node
        cur = head;
        int n = list_size - k - 1;
        while (n--) {
            cur = cur->next;
        }

        ListNode* new_last = cur;
        ListNode* new_head = cur->next;

        new_last->next = NULL;
        dummy.next = new_head;
        last_node->next = head;

        return dummy.next;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

// gtest utility headers
#include "../util/linked_list_gtest.h"

TEST(Problem0061, Example1) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3,4,5]");
    auto k = 2;

    auto result = util::to_linked_list("[4,5,1,2,3]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, Example2) {
    Solution solution;

    auto head = util::to_linked_list("[0,1,2]");
    auto k = 4;

    auto result = util::to_linked_list("[2,0,1]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseEmptyList) {
    Solution solution;

    auto head = util::to_linked_list("[]");
    auto k = 5;

    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseSingleNodeK0) {
    Solution solution;

    auto head = util::to_linked_list("[7]");
    auto k = 0;

    auto result = util::to_linked_list("[7]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseSingleNodeLargeK) {
    Solution solution;

    auto head = util::to_linked_list("[7]");
    auto k = 1'000'000'000;

    auto result = util::to_linked_list("[7]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseKEqualsListLength) {
    Solution solution;

    auto head = util::to_linked_list("[1,3,5]");
    auto k = 3;

    auto result = util::to_linked_list("[1,3,5]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseKIsOne) {
    Solution solution;

    auto head = util::to_linked_list("[2,4,6,8]");
    auto k = 1;

    auto result = util::to_linked_list("[8,2,4,6]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseKMultipleOfLength) {
    Solution solution;

    auto head = util::to_linked_list("[10,20,30]");
    auto k = 6;

    auto result = util::to_linked_list("[10,20,30]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseNegativeValueNodes) {
    Solution solution;

    auto head = util::to_linked_list("[-5,-3,0,2]");
    auto k = 2;

    auto result = util::to_linked_list("[0,2,-5,-3]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

TEST(Problem0061, AdditionalCaseKZeroNonEmpty) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3]");
    auto k = 0;

    auto result = util::to_linked_list("[1,2,3]");

    EXPECT_EQ_LINKED_LIST(solution.rotateRight(head, k), result);
}

#endif
