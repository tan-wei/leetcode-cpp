/**
 * File              : s0047_permutations_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-16 09:11:11
 * Last Modified Date: 2026-10-16 09:16:40
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0047] Permutations II
 *
 * Given a collection of numbers, nums, that might contain duplicates, return
 * all possible unique permutations in any order.
 *
 * Example 1:
 * Input: nums = [1,1,2]
 * Output:
 * [[1,1,2],
 *  [1,2,1],
 *  [2,1,1]]
 * Example 2:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * Constraints:
 * 	1 <= nums.length <= 8
 * 	-10 <= nums[i] <= 10
 *
 */

// problem: https://leetcode.com/problems/permutations-ii/
// discuss: https://leetcode.com/problems/permutations-ii/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        permuteUniqueDfsHelper(nums, result, 0);
        return result;
    }

private:
    void permuteUniqueDfsHelper(vector<int> nums, vector<vector<int>>& result,
                                int begin) {
        if (begin >= nums.size()) {
            result.push_back(nums);
            return;
        }

        for (int i = begin; i < nums.size(); i++) {
            if (i == begin || nums[begin] != nums[i]) {
                swap(nums[begin], nums[i]);
                permuteUniqueDfsHelper(nums, result, begin + 1);
            }
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0047, Example1) {
    Solution solution;

    vector<int> nums = {1, 1, 2};

    vector<vector<int>> result = {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};

    EXPECT_THAT(solution.permuteUnique(nums),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0047, Example2) {
    Solution solution;

    vector<int> nums = {1, 2, 3};

    vector<vector<int>> result = {
        {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

    EXPECT_THAT(solution.permuteUnique(nums),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
