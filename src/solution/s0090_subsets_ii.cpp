/**
 * File              : s0090_subsets_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-28 11:55:37
 * Last Modified Date: 2026-11-28 21:58:39
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0090] Subsets II
 *
 * Given an integer array nums that may contain duplicates, return all possible
 * subsets (the power set). The solution set must not contain duplicate subsets.
 * Return the solution in any order.
 *
 * Example 1:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * Example 2:
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 * Constraints:
 * 	1 <= nums.length <= 10
 * 	-10 <= nums[i] <= 10
 *
 */

// problem: https://leetcode.com/problems/subsets-ii/
// discuss: https://leetcode.com/problems/subsets-ii/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result{vector<int>{}};

        sort(nums.begin(), nums.end());

        int i = 0;
        int sz = nums.size();
        while (i < sz) {
            int dups = 1;
            while (i + 1 < sz && nums[i] == nums[i + 1]) {
                ++i;
                ++dups;
            }
            vector<vector<int>> temp;
            for (auto r : result) {
                temp.push_back(r);
                for (int dup = 1; dup <= dups; dup++) {
                    r.push_back(nums[i]);
                    temp.push_back(r);
                }
            }

            swap(result, temp);
            ++i;
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0090, Example1) {
    Solution solution;

    vector<int> nums = {1, 2, 2};

    vector<vector<int>> result = {{}, {1}, {1, 2}, {1, 2, 2}, {2}, {2, 2}};

    EXPECT_THAT(solution.subsetsWithDup(nums),
                ::testing::UnorderedElementsAreArray(vector<vector<int>>(
                    result.begin(), result.begin() + result.size())));
}

TEST(Problem0090, Example2) {
    Solution solution;

    vector<int> nums = {0};

    vector<vector<int>> result = {{}, {0}};

    EXPECT_THAT(solution.subsetsWithDup(nums),
                ::testing::UnorderedElementsAreArray(vector<vector<int>>(
                    result.begin(), result.begin() + result.size())));
}

TEST(Problem0090, AdditionalCaseAllSame) {
    Solution solution;
    vector<int> nums = {3, 3, 3};
    vector<vector<int>> expect = {{}, {3}, {3, 3}, {3, 3, 3}};
    EXPECT_THAT(solution.subsetsWithDup(nums),
                ::testing::UnorderedElementsAreArray(expect));
}

TEST(Problem0090, AdditionalCaseMultipleDupGroup) {
    Solution solution;
    vector<int> nums = {2, 1, 2, 1, 3};
    vector<vector<int>> expect = {
        {},
        {1},
        {1, 1},
        {1, 2},
        {1, 2, 2},
        {1, 1, 2},
        {1, 1, 2, 2},
        {1, 3},
        {1, 1, 3},
        {1, 2, 3},
        {1, 2, 2, 3},
        {1, 1, 2, 3},
        {1, 1, 2, 2, 3},
        {2},
        {2, 2},
        {2, 3},
        {2, 2, 3},
        {3}};
    EXPECT_THAT(solution.subsetsWithDup(nums),
                ::testing::UnorderedElementsAreArray(expect));
}

TEST(Problem0090, AdditionalCaseNegativeNumber) {
    Solution solution;
    vector<int> nums = {-1, -1, 2};
    vector<vector<int>> expect = {
        {}, {-1}, {-1, -1}, {-1, 2}, {-1, -1, 2}, {2}};
    EXPECT_THAT(solution.subsetsWithDup(nums),
                ::testing::UnorderedElementsAreArray(expect));
}

TEST(Problem0090, AdditionalCaseNoDuplicate) {
    Solution solution;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> expect = {
        {}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}};
    EXPECT_THAT(solution.subsetsWithDup(nums),
                ::testing::UnorderedElementsAreArray(expect));
}

#endif
