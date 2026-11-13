/**
 * File              : s0075_sort_colors.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-13 21:04:19
 * Last Modified Date: 2026-11-13 22:27:54
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0075] Sort Colors
 *
 * You are given an array nums with n objects colored red, white, or blue, sort
 * them in-place so that objects of the same color are adjacent, with the colors
 * in the order red, white, and blue. We will use the integers 0, 1, and 2 to
 * represent the color red, white, and blue, respectively. You must solve this
 * problem without using the library's sort function.
 *
 * Example 1:
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 * Explanation:
 * The array has two 0s, two 1s, and two 2s. Sorting them in-place places all 0s
 * first, then all 1s, then all 2s.
 * Example 2:
 * Input: nums = [2,0,1]
 * Output: [0,1,2]
 * Explanation: The array has one each of 0, 1, and 2, arranged in-place
 * in the order 0, 1, 2.
 *
 * Constraints:
 * 	n == nums.length
 * 	1 <= n <= 300
 * 	nums[i] is either 0, 1, or 2.
 *
 * Follow up: Could you come up with a one-pass algorithm using only constant
 * extra space?
 *
 */

// problem: https://leetcode.com/problems/sort-colors/
// discuss: https://leetcode.com/problems/sort-colors/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int next_1 = -1;
        int next_2 = -1;

        for (int i = 0; i < nums.size(); i++) {
            switch (nums[i]) {
            case 0:
                if (next_1 == -1 || next_2 == -1) {
                    if (next_1 == -1 && next_2 == -1) {
                        // all 0s now, do nothing
                    } else if (next_1 == -1) {
                        // there is no 1
                        swap(nums[next_2], nums[i]);
                        ++next_2;
                    } else {
                        // there is no 2
                        swap(nums[next_1], nums[i]);
                        ++next_1;
                    }
                } else {
                    swap(nums[next_1], nums[i]);
                    swap(nums[next_2], nums[i]);
                    ++next_1;
                    ++next_2;
                }
                break;
            case 1:
                if (next_2 == -1) {
                    // there is no 2, then insert after 0
                    if (next_1 == -1) {
                        next_1 = i;
                    }
                } else {
                    swap(nums[next_2], nums[i]);
                    if (next_1 == -1) {
                        next_1 = next_2;
                    }
                    next_2++;
                }
                break;
            case 2:
                if (next_2 == -1) {
                    next_2 = i;
                }
            default: {
                break;
            }
            }
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0075, Example1) {
    Solution solution;

    vector<int> nums = {2, 0, 2, 1, 1, 0};

    vector<int> result = {0, 0, 1, 1, 2, 2};

    solution.sortColors(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0075, Example2) {
    Solution solution;

    vector<int> nums = {2, 0, 1};

    vector<int> result = {0, 1, 2};

    solution.sortColors(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0075, AdditionalCaseAllZeros) {
    Solution solution;

    vector<int> nums = {0, 0, 0};

    vector<int> result = {0, 0, 0};

    solution.sortColors(nums);
    EXPECT_EQ(nums, result);
}

TEST(Problem0075, AdditionalCaseTwoThenZero) {
    Solution solution;

    vector<int> nums = {2, 0};

    vector<int> result = {0, 2};

    solution.sortColors(nums);
    EXPECT_EQ(nums, result);
}

TEST(Problem0075, AdditionalCaseOneThenZero) {
    Solution solution;

    vector<int> nums = {1, 0};

    vector<int> result = {0, 1};

    solution.sortColors(nums);
    EXPECT_EQ(nums, result);
}

TEST(Problem0075, AdditionalCaseOneAndTwoThenZero) {
    Solution solution;

    vector<int> nums = {1, 2, 0};

    vector<int> result = {0, 1, 2};

    solution.sortColors(nums);
    EXPECT_EQ(nums, result);
}

TEST(Problem0075, AdditionalCaseMultipleOnes) {
    Solution solution;

    vector<int> nums = {1, 1, 1};

    vector<int> result = {1, 1, 1};

    solution.sortColors(nums);
    EXPECT_EQ(nums, result);
}

TEST(Problem0075, AdditionalCaseTwoThenOne) {
    Solution solution;

    vector<int> nums = {2, 1};

    vector<int> result = {1, 2};

    solution.sortColors(nums);
    EXPECT_EQ(nums, result);
}

TEST(Problem0075, AdditionalCaseMultipleTwos) {
    Solution solution;

    vector<int> nums = {2, 2, 2};

    vector<int> result = {2, 2, 2};

    solution.sortColors(nums);
    EXPECT_EQ(nums, result);
}

#endif
