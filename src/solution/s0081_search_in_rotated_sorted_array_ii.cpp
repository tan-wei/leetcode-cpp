/**
 * File              : s0081_search_in_rotated_sorted_array_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-19 19:50:42
 * Last Modified Date: 2026-11-19 21:30:26
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0081] Search in Rotated Sorted Array II
 *
 * There is an integer array nums sorted in non-decreasing order (not
 * necessarily with distinct values). Before being passed to your function, nums
 * is rotated at an unknown pivot index k (0 <= k < nums.length) such that the
 * resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1],
 * ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,4,4,5,6,6,7] might be
 * rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4]. Given the array
 * nums after the rotation and an integer target, return true if target is in
 * nums, or false if it is not in nums. You must decrease the overall operation
 * steps as much as possible.
 *
 * Example 1:
 * Input: nums = [2,5,6,0,0,1,2], target = 0
 * Output: true
 * Example 2:
 * Input: nums = [2,5,6,0,0,1,2], target = 3
 * Output: false
 *
 * Constraints:
 * 	1 <= nums.length <= 5000
 * 	-10^4 <= nums[i] <= 10^4
 * 	nums is guaranteed to be rotated at some pivot.
 * 	-10^4 <= target <= 10^4
 *
 * Follow up: This problem is similar to Search in Rotated Sorted Array, but
 * nums may contain duplicates. Would this affect the runtime complexity? How
 * and why?
 *
 */

// problem: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
// discuss:
// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return true;
            }
            // with duplicates we can have this condition,
            // just update left & right
            if ((nums[left] == nums[mid]) && (nums[right] == nums[mid])) {
                left++;
                right--;
            }
            // first half
            // first half is in order
            else if (nums[left] <= nums[mid]) {
                // target is in first  half
                if ((nums[left] <= target) && (nums[mid] > target)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            // second half
            // second half is order
            // target is in second half
            else {
                if ((nums[mid] < target) && (nums[right] >= target)) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return false;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0081, Example1) {
    Solution solution;

    vector<int> nums = {2, 5, 6, 0, 0, 1, 2};
    auto target = 0;

    auto result = true;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, Example2) {
    Solution solution;

    vector<int> nums = {2, 5, 6, 0, 0, 1, 2};
    auto target = 3;

    auto result = false;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseShrinkDuplicatesFound) {
    Solution solution;

    vector<int> nums = {1, 0, 1, 1, 1};
    auto target = 0;

    auto result = true;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseShrinkDuplicatesNotFound) {
    Solution solution;

    vector<int> nums = {1, 1, 1, 1, 1};
    auto target = 2;

    auto result = false;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseFirstHalfSortedTargetInFirstHalf) {
    Solution solution;

    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    auto target = 5;

    auto result = true;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseFirstHalfSortedTargetNotInFirstHalf) {
    Solution solution;

    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    auto target = 1;

    auto result = true;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseSecondHalfSortedTargetInSecondHalf) {
    Solution solution;

    vector<int> nums = {6, 7, 0, 1, 2, 4, 5};
    auto target = 4;

    auto result = true;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseSecondHalfSortedTargetNotInSecondHalf) {
    Solution solution;

    vector<int> nums = {6, 7, 0, 1, 2, 4, 5};
    auto target = 7;

    auto result = true;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseSingleElementFound) {
    Solution solution;

    vector<int> nums = {1};
    auto target = 1;

    auto result = true;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0081, AdditionalCaseSingleElementNotFound) {
    Solution solution;

    vector<int> nums = {1};
    auto target = 0;

    auto result = false;

    EXPECT_EQ(solution.search(nums, target), result);
}

#endif
