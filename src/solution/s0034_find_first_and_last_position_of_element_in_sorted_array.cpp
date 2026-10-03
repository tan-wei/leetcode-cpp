/**
 * File              :
 * s0034_find_first_and_last_position_of_element_in_sorted_array.cpp Project :
 * leetcode-cpp Author            : Wei Tan <tanwei.winterreise@gmail.com> Date
 * : 2026-10-03 18:36:19 Last Modified Date: 2026-10-03 20:05:53 Last Modified
 * By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0034] Find First and Last Position of Element in Sorted Array
 *
 * Given an array of integers nums sorted in non-decreasing order, find the
 * starting and ending position of a given target value. If target is not found
 * in the array, return [-1, -1]. You must write an algorithm with O(log n)
 * runtime complexity.
 *
 * Example 1:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 * Example 2:
 * Input: nums = [5,7,7,8,8,10], target = 6
 * Output: [-1,-1]
 * Example 3:
 * Input: nums = [], target = 0
 * Output: [-1,-1]
 *
 * Constraints:
 * 	0 <= nums.length <= 10^5
 * 	-10^9 <= nums[i] <= 10^9
 * 	nums is a non-decreasing array.
 * 	-10^9 <= target <= 10^9
 *
 */

// problem:
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// discuss:
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/discuss/

#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto [first, last] = equal_range(nums.begin(), nums.end(), target);

        if (first == last) {
            return {-1, -1};
        }

        int start = static_cast<int>(distance(nums.begin(), first));
        int end = static_cast<int>(distance(nums.begin(), last)) - 1;

        return {start, end};
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0034, Example1) {
    Solution solution;

    vector<int> nums = {5, 7, 7, 8, 8, 10};
    auto target = 8;

    vector<int> result = {3, 4};

    EXPECT_EQ(solution.searchRange(nums, target), result);
}

TEST(Problem0034, Example2) {
    Solution solution;

    vector<int> nums = {5, 7, 7, 8, 8, 10};
    auto target = 6;

    vector<int> result = {-1, -1};

    EXPECT_EQ(solution.searchRange(nums, target), result);
}

TEST(Problem0034, Example3) {
    Solution solution;

    vector<int> nums = {};
    auto target = 0;

    vector<int> result = {-1, -1};

    EXPECT_EQ(solution.searchRange(nums, target), result);
}

#endif
