/**
 * File              : s0055_jump_game.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-24 13:14:47
 * Last Modified Date: 2026-10-24 19:23:25
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0055] Jump Game
 *
 * You are given an integer array nums. You are initially positioned at the
 * array's first index, and each element in the array represents your maximum
 * jump length at that position. Return true if you can reach the last index, or
 * false otherwise.
 *
 * Example 1:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 * Example 2:
 * Input: nums = [3,2,1,0,4]
 * Output: false
 * Explanation: You will always arrive at index 3 no matter what. Its maximum
 * jump length is 0, which makes it impossible to reach the last index.
 *
 * Constraints:
 * 	1 <= nums.length <= 10^4
 * 	0 <= nums[i] <= 10^5
 *
 */

// problem: https://leetcode.com/problems/jump-game/
// discuss: https://leetcode.com/problems/jump-game/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int start = 0;
        int end = 0;
        int terminal = nums.size() - 1;
        int max_end = 0;

        while (start < terminal) {
            for (int j = start; j <= end; j++) {
                if (j + nums[j] > max_end) {
                    max_end = j + nums[j];
                    if (max_end >= terminal) {
                        return true;
                    }
                }
            }
            start = end;
            end = max_end;

            if (start == end && nums[start] == 0) {
                return false;
            }
        }

        return true;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0055, Example1) {
    Solution solution;

    vector<int> nums = {2, 3, 1, 1, 4};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, Example2) {
    Solution solution;

    vector<int> nums = {3, 2, 1, 0, 4};

    auto result = false;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseSingleElementZero) {
    Solution solution;

    vector<int> nums = {0};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseSingleElementNonZero) {
    Solution solution;

    vector<int> nums = {5};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseFirstElementZeroFail) {
    Solution solution;

    vector<int> nums = {0, 1};

    auto result = false;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseTwoElementsReachable) {
    Solution solution;

    vector<int> nums = {1, 0};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseFirstJumpDirectToEnd) {
    Solution solution;

    vector<int> nums = {5, 2, 1};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseSkipOverMiddleZero) {
    Solution solution;

    vector<int> nums = {2, 0, 1, 0};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseAllZerosLongArray) {
    Solution solution;

    vector<int> nums = {0, 0, 0};

    auto result = false;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseConsecutiveStepOne) {
    Solution solution;

    vector<int> nums = {1, 1, 1, 1, 1};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseStuckBeforeEnd) {
    Solution solution;

    vector<int> nums = {2, 1, 0, 3};

    auto result = false;

    EXPECT_EQ(solution.canJump(nums), result);
}

TEST(Problem0055, AdditionalCaseLongJumpCrossZeros) {
    Solution solution;

    vector<int> nums = {3, 0, 0, 0};

    auto result = true;

    EXPECT_EQ(solution.canJump(nums), result);
}

#endif
