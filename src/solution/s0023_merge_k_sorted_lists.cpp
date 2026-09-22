/**
 * File              : s0023_merge_k_sorted_lists.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-22 19:09:56
 * Last Modified Date: 2026-09-22 19:56:21
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0023] Merge k Sorted Lists
 *
 * You are given an array of k linked-lists lists, each linked-list is sorted in
 * ascending order. Merge all the linked-lists into one sorted linked-list and
 * return it.
 *
 * Example 1:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 * Explanation: The linked-lists are:
 * [
 *   1->4->5,
 *   1->3->4,
 *   2->6
 * ]
 * merging them into one sorted linked list:
 * 1->1->2->3->4->4->5->6
 * Example 2:
 * Input: lists = []
 * Output: []
 * Example 3:
 * Input: lists = [[]]
 * Output: []
 *
 * Constraints:
 * 	k == lists.length
 * 	0 <= k <= 10^4
 * 	0 <= lists[i].length <= 500
 * 	-10^4 <= lists[i][j] <= 10^4
 * 	lists[i] is sorted in ascending order.
 * 	The sum of lists[i].length will not exceed 10^4.
 *
 */

// problem: https://leetcode.com/problems/merge-k-sorted-lists/
// discuss: https://leetcode.com/problems/merge-k-sorted-lists/discuss/

#include <list>
#include <queue>
#include <vector>

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](const auto* lhs, const auto* rhs) {
            return lhs->val > rhs->val;
        };

        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q;

        for (auto l : lists) {
            if (l) {
                q.push(l);
            }
        }

        if (q.empty()) {
            return nullptr;
        }

        ListNode* result = q.top();

        q.pop();

        if (result->next) {
            q.push(result->next);
        }

        ListNode* tail = result;

        while (!q.empty()) {
            tail->next = q.top();
            q.pop();
            tail = tail->next;

            if (tail->next) {
                q.push(tail->next);
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

// gtest utility headers
#include "../util/linked_list_gtest.h"

TEST(Problem0023, Example1) {
    Solution solution;

    vector<ListNode*> lists = {
        util::to_linked_list("[1,4,5]"),
        util::to_linked_list("[1,3,4]"),
        util::to_linked_list("[2,6]"),
    };

    auto result = util::to_linked_list("[1,1,2,3,4,4,5,6]");

    EXPECT_EQ_LINKED_LIST(solution.mergeKLists(lists), result);
}

TEST(Problem0023, Example2) {
    Solution solution;

    vector<ListNode*> lists = {};

    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.mergeKLists(lists), result);
}

TEST(Problem0023, Example3) {
    Solution solution;

    vector<ListNode*> lists = {util::to_linked_list("[]")};

    auto result = util::to_linked_list("[]");

    EXPECT_EQ_LINKED_LIST(solution.mergeKLists(lists), result);
}

TEST(Problem0023, AdditionalCaseMixedWithEmptyLists) {
    Solution solution;

    vector<ListNode*> lists = {
        util::to_linked_list("[]"),
        util::to_linked_list("[1,3]"),
        util::to_linked_list("[]"),
        util::to_linked_list("[2,4]"),
    };

    auto result = util::to_linked_list("[1,2,3,4]");

    EXPECT_EQ_LINKED_LIST(solution.mergeKLists(lists), result);
}

TEST(Problem0023, AdditionalCaseUnequalLengths) {
    Solution solution;

    vector<ListNode*> lists = {
        util::to_linked_list("[1]"),
        util::to_linked_list("[0,2,5,7,8]"),
        util::to_linked_list("[3,4]"),
    };

    auto result = util::to_linked_list("[0,1,2,3,4,5,7,8]");

    EXPECT_EQ_LINKED_LIST(solution.mergeKLists(lists), result);
}

TEST(Problem0023, AdditionalCaseWithNegativesAndDuplicates) {
    Solution solution;

    vector<ListNode*> lists = {
        util::to_linked_list("[-2,-1,2]"),
        util::to_linked_list("[-1,0,3]"),
        util::to_linked_list("[-2,1]"),
    };

    auto result = util::to_linked_list("[-2,-2,-1,-1,0,1,2,3]");

    EXPECT_EQ_LINKED_LIST(solution.mergeKLists(lists), result);
}

TEST(Problem0023, AdditionalCaseSingleList) {
    Solution solution;

    vector<ListNode*> lists = {
        util::to_linked_list("[1,2,3]"),
    };

    auto result = util::to_linked_list("[1,2,3]");

    EXPECT_EQ_LINKED_LIST(solution.mergeKLists(lists), result);
}

#endif
