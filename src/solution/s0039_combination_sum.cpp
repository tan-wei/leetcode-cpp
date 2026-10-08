/**
 * File              : s0039_combination_sum.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-08 19:48:53
 * Last Modified Date: 2026-10-08 19:59:44
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0039] Combination Sum
 *
 * Given an array of distinct integers candidates and a target integer target,
 * return a list of all unique combinations of candidates where the chosen
 * numbers sum to target. You may return the combinations in any order. The same
 * number may be chosen from candidates an unlimited number of times. Two
 * combinations are unique if the frequency of at least one of the chosen
 * numbers is different. The test cases are generated such that the number of
 * unique combinations that sum up to target is less than 150 combinations for
 * the given input.
 *
 * Example 1:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 * Explanation:
 * 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple
 * times. 7 is a candidate, and 7 = 7. These are the only two combinations.
 * Example 2:
 * Input: candidates = [2,3,5], target = 8
 * Output: [[2,2,2,2],[2,3,3],[3,5]]
 * Example 3:
 * Input: candidates = [2], target = 1
 * Output: []
 *
 * Constraints:
 * 	1 <= candidates.length <= 30
 * 	2 <= candidates[i] <= 40
 * 	All elements of candidates are distinct.
 * 	1 <= target <= 40
 *
 */

// problem: https://leetcode.com/problems/combination-sum/
// discuss: https://leetcode.com/problems/combination-sum/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        return combinationSumInSortArray(
            candidates, target, candidates.size() - 1);
    }

private:
    vector<vector<int>> combinationSumInSortArray(vector<int>& candidates,
                                                  int target, int n) {
        vector<vector<int>> result;
        if (n <= -1) {
            return result;
        }

        // from the largest
        int elem = candidates[n];
        for (int i = 0;; i++) {
            int remains = target - elem * i;
            if (remains == 0) {
                vector<int> dup_n(i, elem);
                result.push_back(dup_n);
            } else if (remains > 0) {
                vector<vector<int>> try_result =
                    combinationSumInSortArray(candidates, remains, n - 1);
                if (!try_result.empty()) {
                    for (auto v : try_result) {
                        for (int j = 0; j < i; j++) {
                            v.push_back(elem);
                        }
                        result.push_back(v);
                    }
                }
            } else {
                break;
            }
        }
        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0039, Example1) {
    Solution solution;

    vector<int> candidates = {2, 3, 6, 7};
    auto target = 7;

    vector<vector<int>> result = {{2, 2, 3}, {7}};

    EXPECT_THAT(solution.combinationSum(candidates, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0039, Example2) {
    Solution solution;

    vector<int> candidates = {2, 3, 5};
    auto target = 8;

    vector<vector<int>> result = {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}};

    EXPECT_THAT(solution.combinationSum(candidates, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0039, Example3) {
    Solution solution;

    vector<int> candidates = {2};
    auto target = 1;

    vector<vector<int>> result = {};

    EXPECT_THAT(solution.combinationSum(candidates, target),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
