/**
 * File              : s0077_combinations.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-15 11:38:56
 * Last Modified Date: 2026-11-15 17:21:33
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0077] Combinations
 *
 * Given two integers n and k, return all possible combinations of k numbers
 * chosen from the range [1, n]. You may return the answer in any order.
 *
 * Example 1:
 * Input: n = 4, k = 2
 * Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 * Explanation: There are 4 choose 2 = 6 total combinations.
 * Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to
 * be the same combination.
 * Example 2:
 * Input: n = 1, k = 1
 * Output: [[1]]
 * Explanation: There is 1 choose 1 = 1 total combination.
 *
 * Constraints:
 * 	1 <= n <= 20
 * 	1 <= k <= n
 *
 */

// problem: https://leetcode.com/problems/combinations/
// discuss: https://leetcode.com/problems/combinations/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        if (n < k) {
            // Just return the empty result
        } else if (k == 1) {
            for (int i = 1; i <= n; i++) {
                result.push_back(vector<int>{i});
            }
        } else {
            for (int last = k; last <= n; last++) {
                vector<vector<int>> result_n_1 = combine(last - 1, k - 1);
                for (auto v : result_n_1) {
                    v.push_back(last);
                    result.push_back(v);
                }
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0077, Example1) {
    Solution solution;

    auto n = 4;
    auto k = 2;

    vector<vector<int>> result = {
        {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};

    EXPECT_THAT(solution.combine(n, k),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0077, Example2) {
    Solution solution;

    auto n = 1;
    auto k = 1;

    vector<vector<int>> result = {{1}};

    EXPECT_THAT(solution.combine(n, k),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
