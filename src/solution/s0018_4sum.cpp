/**
 * File              : s0018_4sum.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-17 19:24:36
 * Last Modified Date: 2026-09-17 22:02:23
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0018] 4Sum
 *
 * Given an array nums of n integers, return an array of all the unique
 * quadruplets [nums[a], nums[b], nums[c], nums[d]] such that: 0 <= a, b, c, d <
 * n a, b, c, and d are distinct. nums[a] + nums[b] + nums[c] + nums[d] ==
 * target You may return the answer in any order.
 *
 * Example 1:
 * Input: nums = [1,0,-1,0,-2,2], target = 0
 * Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 * Example 2:
 * Input: nums = [2,2,2,2,2], target = 8
 * Output: [[2,2,2,2]]
 *
 * Constraints:
 * 	1 <= nums.length <= 200
 * 	-10^9 <= nums[i] <= 10^9
 * 	-10^9 <= target <= 10^9
 *
 */

// problem: https://leetcode.com/problems/4sum/
// discuss: https://leetcode.com/problems/4sum/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }

        vector<vector<int>> result;

        sort(nums.begin(), nums.end());

        for (size_t i = 0; i < nums.size() - 3;) {
            for (size_t j = i + 1; j < nums.size() - 2;) {
                long long target_i_j =
                    static_cast<long long>(target) - nums[i] - nums[j];
                size_t left = j + 1;
                size_t right = nums.size() - 1;
                while (left < right) {
                    auto nums_left = nums[left];
                    auto nums_right = nums[right];

                    if (nums_left + nums_right == target_i_j) {
                        result.push_back(
                            {nums[i], nums[j], nums_left, nums_right});
                        while ((left < right) &&
                               (nums_left == nums[left + 1])) {
                            ++left;
                        }
                        while ((right > left) &&
                               (nums_right == nums[right - 1])) {
                            --right;
                        }
                        ++left;
                        --right;
                    } else if (nums_left + nums_right < target_i_j) {
                        while ((left < right) &&
                               (nums_left == nums[left + 1])) {
                            ++left;
                        }
                        ++left;
                    } else {
                        while ((right > left) &&
                               (nums_right == nums[right - 1])) {
                            --right;
                        }
                        --right;
                    }
                }
                while ((j < nums.size() - 1) && (nums[j] == nums[j + 1])) {
                    ++j;
                }
                ++j;
            }

            while ((i < nums.size() - 3) && (nums[i] == nums[i + 1])) {
                ++i;
            }
            ++i;
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0018, Example1) {
    Solution solution;

    vector<int> nums = {1, 0, -1, 0, -2, 2};
    auto target = 0;

    vector<vector<int>> result = {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, Example2) {
    Solution solution;

    vector<int> nums = {2, 2, 2, 2, 2};
    auto target = 8;

    vector<vector<int>> result = {{2, 2, 2, 2}};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, RuntimeErrorOverFlowCase1) {
    Solution solution;

    vector<int> nums = {1'000'000'000, 1'000'000'000, 1'000'000'000,
                        1'000'000'000};
    auto target = -294'967'296;

    vector<vector<int>> result = {};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, AdditionalCaseLessThanFourElements) {
    Solution solution;

    vector<int> nums = {1, 2, 3};
    auto target = 6;

    vector<vector<int>> result = {};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, AdditionalCaseAllZerosTargetZero) {
    Solution solution;

    vector<int> nums = {0, 0, 0, 0, 0, 0};
    auto target = 0;

    vector<vector<int>> result = {{0, 0, 0, 0}};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, AdditionalCaseIntegerOverflowAvoidance) {
    Solution solution;

    vector<int> nums = {1'000'000'000, 1'000'000'000, 1'000'000'000,
                        1'000'000'000};
    auto target = -294'967'296;

    vector<vector<int>> result = {};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, AdditionalCaseHeavyDuplicatesWithMultipleQuadruplets) {
    Solution solution;

    vector<int> nums = {-3, -1, 0, 2, 4, 5, 0, -1, -3, -1, 2};
    auto target = 0;

    vector<vector<int>> result = {
        {-3, -3, 2, 4},
        {-3, -1, -1, 5},
        {-3, -1, 0, 4},
        {-3, -1, 2, 2},
        {-1, -1, 0, 2}};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, TimeLimitExceededCaseLargeAllDuplicates) {
    Solution solution;

    vector<int> nums(200, 0);
    auto target = 0;

    vector<vector<int>> result = {{0, 0, 0, 0}};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0018, TimeLimitExceededCaseLargeWorstCaseNoQuadruplets) {
    Solution solution;

    vector<int> nums;
    nums.reserve(200);

    for (int i = 1; i <= 200; ++i) {
        nums.push_back(i);
    }
    auto target = -100;

    vector<vector<int>> result = {};

    EXPECT_THAT(solution.fourSum(nums, target),
                ::testing::UnorderedElementsAreArray(result));
}

#endif
