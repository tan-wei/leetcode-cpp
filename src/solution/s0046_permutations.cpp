/**
 * File              : s0046_permutations.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-15 20:49:52
 * Last Modified Date: 2026-10-15 22:19:59
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0046] Permutations
 *
 * Given an array nums of distinct integers, return all the possible
 * permutations. You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * Example 2:
 * Input: nums = [0,1]
 * Output: [[0,1],[1,0]]
 * Example 3:
 * Input: nums = [1]
 * Output: [[1]]
 *
 * Constraints:
 * 	1 <= nums.length <= 6
 * 	-10 <= nums[i] <= 10
 * 	All the integers of nums are unique.
 *
 */

// problem: https://leetcode.com/problems/permutations/
// discuss: https://leetcode.com/problems/permutations/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        permuteDfsHelper(nums, result, 0);
        return result;
    }

private:
    void permuteDfsHelper(vector<int>& nums, vector<vector<int>>& result,
                          int begin) {
        if (begin >= nums.size()) {
            result.push_back(nums);
            return;
        }

        for (int i = begin; i < nums.size(); i++) {
            swap(nums[begin], nums[i]);
            permuteDfsHelper(nums, result, begin + 1);
            swap(nums[begin], nums[i]);
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0046, Example1) {
    Solution solution;

    vector<int> nums = {1, 2, 3};

    vector<vector<int>> result = {
        {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

    EXPECT_THAT(solution.permute(nums),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0046, Example2) {
    Solution solution;

    vector<int> nums = {0, 1};

    vector<vector<int>> result = {{0, 1}, {1, 0}};

    EXPECT_THAT(solution.permute(nums),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0046, Example3) {
    Solution solution;

    vector<int> nums = {1};

    vector<vector<int>> result = {{1}};

    EXPECT_THAT(solution.permute(nums),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
