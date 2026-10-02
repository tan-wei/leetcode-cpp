/**
 * File              : s0033_search_in_rotated_sorted_array.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-02 18:34:12
 * Last Modified Date: 2026-10-02 20:49:56
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0033] Search in Rotated Sorted Array
 *
 * There is an integer array nums sorted in ascending order (with distinct
 * values). Prior to being passed to your function, nums is possibly left
 * rotated at an unknown index k (1 <= k < nums.length) such that the resulting
 * array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ...,
 * nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by
 * 3 indices and become [4,5,6,7,0,1,2]. Given the array nums after the possible
 * rotation and an integer target, return the index of target if it is in nums,
 * or -1 if it is not in nums. You must write an algorithm with O(log n) runtime
 * complexity.
 *
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 *
 * Constraints:
 * 	1 <= nums.length <= 5000
 * 	-10^4 <= nums[i] <= 10^4
 * 	All values of nums are unique.
 * 	nums is an ascending array that is possibly rotated.
 * 	-10^4 <= target <= 10^4
 *
 */

// problem: https://leetcode.com/problems/search-in-rotated-sorted-array/
// discuss:
// https://leetcode.com/problems/search-in-rotated-sorted-array/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int search(vector<int>& nums, int target) { return 0; }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0033, Example1) {
    GTEST_SKIP() << "Can't solve, skip";
    Solution solution;

    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    auto target = 0;

    auto result = 4;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0033, Example2) {
    GTEST_SKIP() << "Can't solve, skip";
    Solution solution;

    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    auto target = 3;

    auto result = -1;

    EXPECT_EQ(solution.search(nums, target), result);
}

TEST(Problem0033, Example3) {
    GTEST_SKIP() << "Can't solve, skip";
    Solution solution;

    vector<int> nums = {1};
    auto target = 0;

    auto result = -1;

    EXPECT_EQ(solution.search(nums, target), result);
}

#endif
