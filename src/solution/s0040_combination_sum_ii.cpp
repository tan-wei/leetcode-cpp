/**
 * File              : s0040_combination_sum_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-09 20:57:38
 * Last Modified Date: 2026-10-09 22:59:57
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
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> ds;
        combinationSum2DfsHelper(0, target, candidates, result, ds);
        return result;
    }

private:
    void combinationSum2DfsHelper(int ind, int target, vector<int>& candidate,
                                  vector<vector<int>>& result,
                                  vector<int>& ds) {
        if (target == 0) {
            result.push_back(ds);
            return;
        }
        for (int i = ind; i < candidate.size(); i++) {
            if (i > ind && candidate[i] == candidate[i - 1]) {
                continue;
            }
            if (candidate[i] > target) {
                break;
            }
            ds.push_back(candidate[i]);
            combinationSum2DfsHelper(
                i + 1, target - candidate[i], candidate, result, ds);
            ds.pop_back();
        }
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
