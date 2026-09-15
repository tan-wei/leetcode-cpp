/**
 * File              : s0016_3sum_closest.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-15 18:49:15
 * Last Modified Date: 2026-09-15 20:24:41
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0016] 3Sum Closest
 *
 * You are given an integer array nums of length n and an integer target.
 * Find three integers at distinct indices in nums such that the sum is closest
 * to target. Return the sum of the three integers. You may assume that each
 * input would have exactly one solution.
 *
 * Example 1:
 * Input: nums = [-1,2,1,-4], target = 1
 * Output: 2
 * Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 * Example 2:
 * Input: nums = [0,0,0], target = 1
 * Output: 0
 * Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).
 *
 * Constraints:
 * 	3 <= nums.length <= 500
 * 	-1000 <= nums[i] <= 1000
 * 	-10^4 <= target <= 10^4
 *
 */

// problem: https://leetcode.com/problems/3sum-closest/
// discuss: https://leetcode.com/problems/3sum-closest/discuss/

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() <= 3) {
            return accumulate(nums.begin(), nums.end(), 0);
        }

        sort(nums.begin(), nums.end());

        int min_delta = numeric_limits<int>::max();
        int result = 0;

        for (size_t i = 0; i < nums.size() - 2; i++) {
            auto left = i + 1;
            auto right = nums.size() - 1;
            auto temp_i = nums[i];

            while (left < right) {
                auto temp_left = nums[left];
                auto temp_right = nums[right];

                if (temp_i + temp_left + temp_right < target) {
                    auto delta = target - (temp_i + temp_left + temp_right);

                    ++left;
                    while (left < right) {
                        if (nums[left] - temp_left < delta) {
                            ++left;
                        } else {
                            break;
                        }
                    }

                    auto d1 = temp_i + nums[left - 1] + temp_right - target;
                    auto d2 = numeric_limits<int>::max();
                    if (left != right) {
                        d2 = temp_i + nums[left] + temp_right - target;
                    }

                    if (d1 == 0 || d2 == 0) {
                        return target;
                    }

                    if ((abs(d1) > abs(d2)) && (min_delta > abs(d2))) {
                        min_delta = abs(d2);
                        result = temp_i + nums[left] + temp_right;
                    } else if ((abs(d2) > abs(d1)) && (min_delta > abs(d1))) {
                        min_delta = abs(d1);
                        result = temp_i + nums[left - 1] + temp_right;
                    }

                } else if (temp_i + temp_left + temp_right > target) {
                    auto delta = (temp_i + temp_left + temp_right) - target;

                    --right;
                    while (left < right) {
                        if (temp_right - nums[right] < delta) {
                            --right;
                        } else {
                            break;
                        }
                    }

                    auto d1 = temp_i + temp_left + nums[right + 1] - target;
                    auto d2 = numeric_limits<int>::max();

                    if (left != right) {
                        d2 = temp_i + temp_left + nums[right] - target;
                    }

                    if (d1 == 0 || d2 == 0) {
                        return target;
                    }

                    if ((abs(d1) > abs(d2)) && (min_delta > abs(d2))) {
                        min_delta = abs(d2);
                        result = temp_i + temp_left + nums[right];
                    } else if ((abs(d2) > abs(d1)) && (min_delta > abs(d1))) {
                        min_delta = abs(d1);
                        result = temp_i + temp_left + nums[right + 1];
                    }
                } else {
                    return target;
                }
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0016, Example1) {
    Solution solution;

    vector<int> nums = {-1, 2, 1, -4};
    auto target = 1;

    auto result = 2;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

TEST(Problem0016, Example2) {
    Solution solution;

    vector<int> nums = {0, 0, 0};
    auto target = 1;

    auto result = 0;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

TEST(Problem0016, AdditionalCaseExactlyThreeElements) {
    Solution solution;

    vector<int> nums = {1, 1, 1};
    auto target = -100;

    auto result = 3;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

TEST(Problem0016, AdditionalCaseExactMatchTarget) {
    Solution solution;

    vector<int> nums = {-3, -1, 1, 2, 11, 4};
    auto target = 0;

    auto result = 0;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

TEST(Problem0016, AdditionalCaseHeavyDuplicates) {
    Solution solution;

    vector<int> nums = {1, 1, 1, 1, 1, 5, 5, 5};
    auto target = 4;

    auto result = 3;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

TEST(Problem0016, AdditionalCaseBoundaryValuesConstraints) {
    Solution solution;

    vector<int> nums = {-1'000, -1'000, 1'000, 1'000};
    auto target = 10'000;

    auto result = 1'000;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

TEST(Problem0016, TimeLimitExceededCaseLargeSortedAscending) {
    Solution solution;

    vector<int> nums;
    nums.reserve(500);
    for (int i = 1; i <= 500; ++i) {
        nums.push_back(i);
    }
    auto target = 1'490;

    auto result = 1'490;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

TEST(Problem0016, TimeLimitExceededCaseLargeAllDuplicates) {
    Solution solution;

    vector<int> nums(500, 2);
    auto target = 10;

    auto result = 6;

    EXPECT_EQ(solution.threeSumClosest(nums, target), result);
}

#endif
