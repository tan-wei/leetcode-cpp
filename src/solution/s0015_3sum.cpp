/**
 * File              : s0015_3sum.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-14 19:39:17
 * Last Modified Date: 2026-09-14 20:14:17
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0015] 3Sum
 *
 * Given an integer array nums, return all the triplets [nums[i], nums[j],
 * nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] +
 * nums[k] == 0. Notice that the solution set must not contain duplicate
 * triplets.
 *
 * Example 1:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation:
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 * The distinct triplets are [-1,0,1] and [-1,-1,2].
 * Notice that the order of the output and the order of the triplets does not
 * matter.
 * Example 2: Input: nums = [0,1,1]
 * Output: []
 * Explanation: The only possible triplet does not sum up to 0.
 * Example 3: Input: nums = [0,0,0]
 * Output: [[0,0,0]]
 * Explanation: The only possible triplet sums up to 0.
 *
 * Constraints:
 * 	3 <= nums.length <= 3000
 * 	-10^5 <= nums[i] <= 10^5
 *
 */

// problem: https://leetcode.com/problems/3sum/
// discuss: https://leetcode.com/problems/3sum/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() <= 2) {
            return {};
        }

        vector<vector<int>> result;

        sort(nums.begin(), nums.end());

        for (size_t i = 0; i < nums.size() - 2;) {
            auto left = i + 1;
            auto right = nums.size() - 1;
            auto target = -nums[i];

            while (left < right) {
                auto a = nums[left];
                auto b = nums[right];

                if (a + b == target) {
                    result.push_back({-target, a, b});
                    while ((left < right) && (a == nums[left + 1])) {
                        ++left;
                    }
                    while ((right > left) && (b == nums[right - 1])) {
                        --right;
                    }
                    ++left;
                    --right;
                } else if (a + b < target) {
                    while ((left < right) && (a == nums[left + 1])) {
                        ++left;
                    }
                    ++left;
                } else {
                    while ((right > left) && (b == nums[right - 1])) {
                        --right;
                    }
                    --right;
                }
            }

            while ((i < nums.size() - 1) && (-target == nums[i + 1])) {
                ++i;
            }

            ++i;
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0015, Example1) {
    Solution solution;

    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    vector<vector<int>> result = {{-1, -1, 2}, {-1, 0, 1}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, Example2) {
    Solution solution;

    vector<int> nums = {0, 1, 1};

    vector<vector<int>> result = {};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, Example3) {
    Solution solution;

    vector<int> nums = {0, 0, 0};

    vector<vector<int>> result = {{0, 0, 0}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseLessThanThreeElements) {
    Solution solution;

    vector<int> nums = {1, 2};

    vector<vector<int>> result = {};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseExactlyThreeNoZeroSum) {
    Solution solution;

    vector<int> nums = {1, 2, 3};

    vector<vector<int>> result = {};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseExactlyThreeZeroSum) {
    Solution solution;

    vector<int> nums = {-1, 0, 1};

    vector<vector<int>> result = {{-1, 0, 1}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseAllZeros) {
    Solution solution;

    vector<int> nums = {0, 0, 0, 0, 0, 0};

    vector<vector<int>> result = {{0, 0, 0}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseAllPositiveNumbers) {
    Solution solution;

    vector<int> nums = {1, 2, 3, 4, 5, 6};

    vector<vector<int>> result = {};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseAllNegativeNumbers) {
    Solution solution;

    vector<int> nums = {-6, -5, -4, -3, -2, -1};

    vector<vector<int>> result = {};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseHeavyDuplicatesWithFewMatches) {
    Solution solution;

    vector<int> nums = {-2, -2, -2, -2, 0, 0, 0, 2, 2, 2, 2};

    vector<vector<int>> result = {{-2, 0, 2}, {0, 0, 0}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseMultipleUniqueTriplets) {
    Solution solution;

    vector<int> nums = {-4, -1, -1, 0, 1, 2, -1, -4};

    vector<vector<int>> result = {{-1, -1, 2}, {-1, 0, 1}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, AdditionalCaseLargeValuesNearConstraints) {
    Solution solution;

    vector<int> nums = {-100'000, 0, 100'000, -50'000, 50'000, 0};

    vector<vector<int>> result = {{-100'000, 0, 100'000}, {-50'000, 0, 50'000}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, TimeLimitExceededCaseLargeAllZeros) {
    Solution solution;

    vector<int> nums(3'000, 0);

    vector<vector<int>> result = {{0, 0, 0}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, TimeLimitExceededCaseLargeWorstCaseNoTriplets) {
    Solution solution;

    vector<int> nums;
    nums.reserve(3'000);
    for (int i = 1; i <= 3'000; ++i) {
        nums.push_back(i);
    }

    vector<vector<int>> result = {};

    EXPECT_EQ(solution.threeSum(nums), result);
}

TEST(Problem0015, TimeLimitExceededCaseLargeManyDuplicatesNegativeAndPositive) {
    Solution solution;

    vector<int> nums;
    nums.reserve(3'000);
    for (int i = 0; i < 1'000; ++i) {
        nums.push_back(-2);
    }
    for (int i = 0; i < 2'000; ++i) {
        nums.push_back(1);
    }

    vector<vector<int>> result = {{-2, 1, 1}};

    EXPECT_EQ(solution.threeSum(nums), result);
}

#endif
