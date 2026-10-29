/**
 * File              : s0060_permutation_sequence.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-29 21:09:53
 * Last Modified Date: 2026-10-29 21:37:27
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0060] Permutation Sequence
 *
 * The set [1, 2, 3, ..., n] contains a total of n! unique permutations.
 * By listing and labeling all of the permutations in order, we get the
 * following sequence for n = 3: "123" "132" "213" "231" "312" "321" Given n and
 * k, return the k^th permutation sequence.
 *
 * Example 1:
 * Input: n = 3, k = 3
 * Output: "213"
 * Example 2:
 * Input: n = 4, k = 9
 * Output: "2314"
 * Example 3:
 * Input: n = 3, k = 1
 * Output: "123"
 *
 * Constraints:
 * 	1 <= n <= 9
 * 	1 <= k <= n!
 *
 */

// problem: https://leetcode.com/problems/permutation-sequence/
// discuss: https://leetcode.com/problems/permutation-sequence/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    string getPermutation(int n, int k) { return std::string(); }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0060, Example1) {
    GTEST_SKIP() << "A hard one should be retried";
    Solution solution;

    auto n = 3;
    auto k = 3;

    auto result = "213"s;

    EXPECT_EQ(solution.getPermutation(n, k), result);
}

TEST(Problem0060, Example2) {
    GTEST_SKIP() << "A hard one should be retried";
    Solution solution;

    auto n = 4;
    auto k = 9;

    auto result = "2314"s;

    EXPECT_EQ(solution.getPermutation(n, k), result);
}

TEST(Problem0060, Example3) {
    GTEST_SKIP() << "A hard one should be retried";
    Solution solution;

    auto n = 3;
    auto k = 1;

    auto result = "123"s;

    EXPECT_EQ(solution.getPermutation(n, k), result);
}

#endif
