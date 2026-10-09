/**
 * File              : s0040_combination_sum_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-09 20:57:38
 * Last Modified Date: 2026-10-09 22:27:56
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0040] Combination Sum II
 *
 * Given a collection of candidate numbers (candidates) and a target number
 * (target), find all unique combinations in candidates where the candidate
 * numbers sum to target. Each number in candidates may only be used once in the
 * combination. Note: The solution set must not contain duplicate combinations.
 *
 * Example 1:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output:
 * [
 * [1,1,6],
 * [1,2,5],
 * [1,7],
 * [2,6]
 * ]
 * Example 2:
 * Input: candidates = [2,5,2,1,2], target = 5
 * Output:
 * [
 * [1,2,2],
 * [5]
 * ]
 *
 * Constraints:
 * 	1 <= candidates.length <= 100
 * 	1 <= candidates[i] <= 50
 * 	1 <= target <= 30
 *
 */

// problem: https://leetcode.com/problems/combination-sum-ii/
// discuss: https://leetcode.com/problems/combination-sum-ii/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        sort(candidates.begin(), candidates.end());
        result = combinationSumInSubArray2(
            candidates, target, candidates.size() - 1);
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }

private:
    vector<vector<int>> combinationSumInSubArray2(vector<int>& candidates,
                                                  int target, int n) {
        vector<vector<int>> result;
        if (n <= -1) {
            return result;
        }

        int elem = candidates[n];
        for (int i = 0; i <= 1; i++) {
            int remains = target - elem * i;
            if (remains == 0) {
                vector<int> dup_n(statica_cast<int>(i), elem);
                result.push_back(dup_n);
            } else if (remains > 0) {
                vector<vector<int>> try_result =
                    combinationSumInSubArray2(candidates, remains, n - 1);
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
#include <gtest/gtest.h>

TEST(Problem0040, Example1) {
    Solution solution;

    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    auto target = 8;

    vector<vector<int>> result = {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}};

    EXPECT_EQ(solution.combinationSum2(candidates, target), result);
}

TEST(Problem0040, Example2) {
    Solution solution;

    vector<int> candidates = {2, 5, 2, 1, 2};
    auto target = 5;

    vector<vector<int>> result = {{1, 2, 2}, {5}};

    EXPECT_EQ(solution.combinationSum2(candidates, target), result);
}

#endif
