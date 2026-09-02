#ifndef LEETCODE_UTIL_LINKED_LIST_GTEST_H
#define LEETCODE_UTIL_LINKED_LIST_GTEST_H

#include "linked_list.h"

#include <gtest/gtest.h>

// GTest printer for ListNode* -- enables readable output on EXPECT_* failure
inline void PrintTo(const util::ListNode* h, std::ostream* os) {
    *os << util::to_string(h);
}

// GTest predicate formatter -- enables EXPECT_PRED_FORMAT2(list_equal, ...)
// with automatic diff output on failure
inline ::testing::AssertionResult list_equal(
    const char* a_expr, const char* b_expr, const util::ListNode* a,
    const util::ListNode* b) {
    const util::ListNode* pa = a;
    const util::ListNode* pb = b;
    while (pa && pb) {
        if (pa->val != pb->val) {
            return ::testing::AssertionFailure()
                   << "Mismatch at node:\n"
                   << a_expr << " = " << util::to_string(a) << "\n"
                   << b_expr << " = " << util::to_string(b);
        }
        pa = pa->next;
        pb = pb->next;
    }
    if (pa != pb) {
        return ::testing::AssertionFailure()
               << "Length mismatch:\n"
               << a_expr << " = " << util::to_string(a) << "\n"
               << b_expr << " = " << util::to_string(b);
    }
    return ::testing::AssertionSuccess();
}

#endif // LEETCODE_UTIL_LINKED_LIST_GTEST_H
