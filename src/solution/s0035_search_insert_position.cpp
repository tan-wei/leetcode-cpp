/**
 * File              : s0035_search_insert_position.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-04 12:08:31
 * Last Modified Date: 2026-10-04 21:38:13
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0035] Search Insert Position
 *
 * Given a sorted array of distinct integers and a target value, return the
 * index if the target is found. If not, return the index where it would be if
 * it were inserted in order. You must write an algorithm with O(log n) runtime
 * complexity.
 *
 * Example 1:
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 * Example 2:
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 * Example 3:
 * Input: nums = [1,3,5,6], target = 7
 * Output: 4
 *
 * Constraints:
 * 	1 <= nums.length <= 10^4
 * 	-10^4 <= nums[i] <= 10^4
 * 	nums contains distinct values sorted in ascending order.
 * 	-10^4 <= target <= 10^4
 *
 */

// problem: https://leetcode.com/problems/search-insert-position/
// discuss: https://leetcode.com/problems/search-insert-position/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        auto iter = lower_bound(nums.begin(), nums.end(), target);

        return static_cast<int>(distance(nums.begin(), iter));
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0035, Example1) {
    Solution solution;

    vector<int> nums = {1, 3, 5, 6};
    auto target = 5;

    auto result = 2;

    EXPECT_EQ(solution.searchInsert(nums, target), result);
}

TEST(Problem0035, Example2) {
    Solution solution;

    vector<int> nums = {1, 3, 5, 6};
    auto target = 2;

    auto result = 1;

    EXPECT_EQ(solution.searchInsert(nums, target), result);
}

TEST(Problem0035, Example3) {
    Solution solution;

    vector<int> nums = {1, 3, 5, 6};
    auto target = 7;

    auto result = 4;

    EXPECT_EQ(solution.searchInsert(nums, target), result);
}

#endif
