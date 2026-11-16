/**
 * File              : s0078_subsets.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-16 19:45:20
 * Last Modified Date: 2026-11-16 21:40:50
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0078] Subsets
 *
 * Given an integer array nums of unique elements, return all possible subsets
 * (the power set). The solution set must not contain duplicate subsets. Return
 * the solution in any order.
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 * Example 2:
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 * Constraints:
 * 	1 <= nums.length <= 10
 * 	-10 <= nums[i] <= 10
 * 	All the numbers of nums are unique.
 *
 */

// problem: https://leetcode.com/problems/subsets/
// discuss: https://leetcode.com/problems/subsets/discuss/

#include <utility>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result{vector<int>{}};

        for (auto num : nums) {
            vector<vector<int>> temp;

            for (auto r : result) {
                temp.push_back(r);
                r.push_back(num);
                temp.push_back(r);
            }

            swap(result, temp);
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0078, Example1) {
    Solution solution;

    vector<int> nums = {1, 2, 3};

    vector<vector<int>> result = {
        {}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}};

    EXPECT_THAT(solution.subsets(nums),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0078, Example2) {
    Solution solution;

    vector<int> nums = {0};

    vector<vector<int>> result = {{}, {0}};

    EXPECT_THAT(solution.subsets(nums),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
