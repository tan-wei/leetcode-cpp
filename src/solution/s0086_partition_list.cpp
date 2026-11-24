/**
 * File              : s0086_partition_list.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-24 19:08:17
 * Last Modified Date: 2026-11-24 21:55:18
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0086] Partition List
 *
 * Given the head of a linked list and a value x, partition it such that all
 * nodes less than x come before nodes greater than or equal to x. You should
 * preserve the original relative order of the nodes in each of the two
 * partitions.
 *
 * Example 1:
 * Input: head = [1,4,3,2,5,2], x = 3
 * Output: [1,2,2,4,3,5]
 * Example 2:
 * Input: head = [2,1], x = 2
 * Output: [1,2]
 *
 * Constraints:
 * 	The number of nodes in the list is in the range [0, 200].
 * 	-100 <= Node.val <= 100
 * 	-200 <= x <= 200
 *
 */

// problem: https://leetcode.com/problems/partition-list/
// discuss: https://leetcode.com/problems/partition-list/discuss/

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
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode dummy(0);
        dummy.next = head;

        ListNode* cur = head;
        ListNode* less_node = &dummy;
        ListNode* former_node = &dummy;

        while (cur) {
            if (cur->val < x) {
                former_node->next = cur->next;
                cur->next = less_node->next;
                less_node->next = cur;

                less_node = cur;
            }

            former_node = cur;
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

TEST(Problem0086, Example1) {
    Solution solution;

    auto head = util::to_linked_list("[1,4,3,2,5,2]");
    auto x = 3;

    auto result = util::to_linked_list("[1,2,2,4,3,5]");
    ;

    EXPECT_EQ_LINKED_LIST(solution.partition(head, x), result);
}

TEST(Problem0086, Example2) {
    Solution solution;

    auto head = util::to_linked_list("[2,1]");
    auto x = 2;

    auto result = util::to_linked_list("[1,2]");

    EXPECT_EQ_LINKED_LIST(solution.partition(head, x), result);
}

TEST(Problem0086, AdditionalCaseEmptyList) {
    Solution solution;

    auto head = util::to_linked_list("[]");
    auto x = 1;

    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.partition(head, x), result);
}

TEST(Problem0086, AdditionalCaseAllLessThanX) {
    Solution solution;

    auto head = util::to_linked_list("[1,2,3]");
    auto x = 5;

    auto result = util::to_linked_list("[1,2,3]");

    EXPECT_EQ_LINKED_LIST(solution.partition(head, x), result);
}

TEST(Problem0086, AdditionalCaseAllGreaterOrEqualToX) {
    Solution solution;

    auto head = util::to_linked_list("[3,4,5]");
    auto x = 3;

    auto result = util::to_linked_list("[3,4,5]");

    EXPECT_EQ_LINKED_LIST(solution.partition(head, x), result);
}

TEST(Problem0086, AdditionalCaseSingleNode) {
    Solution solution;

    auto head = util::to_linked_list("[1]");
    auto x = 2;

    auto result = util::to_linked_list("[1]");

    EXPECT_EQ_LINKED_LIST(solution.partition(head, x), result);
}

TEST(Problem0086, AdditionalCaseEqualToXPreservesOrder) {
    Solution solution;

    auto head = util::to_linked_list("[3,1,3,2,3]");
    auto x = 3;

    auto result = util::to_linked_list("[1,2,3,3,3]");

    EXPECT_EQ_LINKED_LIST(solution.partition(head, x), result);
}

#endif
