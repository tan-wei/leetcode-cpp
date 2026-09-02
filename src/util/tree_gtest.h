#ifndef LEETCODE_UTIL_TREE_GTEST_H
#define LEETCODE_UTIL_TREE_GTEST_H

#include "tree.h"

#include <gtest/gtest.h>

// GTest printer for TreeNode* -- enables readable output on EXPECT_* failure
inline void PrintTo(const util::TreeNode* h, std::ostream* os) {
    *os << util::to_string(const_cast<util::TreeNode*>(h));
}

// GTest predicate formatter -- enables EXPECT_PRED_FORMAT2(tree_equal, ...)
// with automatic diff output on failure
inline ::testing::AssertionResult tree_equal(
    const char* a_expr, const char* b_expr, const util::TreeNode* a,
    const util::TreeNode* b) {
    if (a == nullptr && b == nullptr) {
        return ::testing::AssertionSuccess();
    }
    if (a == nullptr || b == nullptr) {
        return ::testing::AssertionFailure()
               << "One tree is null, the other is not:\n"
               << a_expr << " = "
               << util::to_string(const_cast<util::TreeNode*>(a)) << "\n"
               << b_expr << " = "
               << util::to_string(const_cast<util::TreeNode*>(b));
    }
    if (a->val != b->val) {
        return ::testing::AssertionFailure()
               << "Mismatch at root value:\n"
               << a_expr << " = "
               << util::to_string(const_cast<util::TreeNode*>(a)) << "\n"
               << b_expr << " = "
               << util::to_string(const_cast<util::TreeNode*>(b));
    }
    // Recurse into children
    auto left_result = tree_equal(a_expr, b_expr, a->left, b->left);
    if (!left_result) {
        return left_result;
    }
    return tree_equal(a_expr, b_expr, a->right, b->right);
}

#endif // LEETCODE_UTIL_TREE_GTEST_H
