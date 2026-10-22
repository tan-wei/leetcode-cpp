/**
 * File              : s0053_maximum_subarray.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-22 19:02:34
 * Last Modified Date: 2026-10-22 20:22:31
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0053] Maximum Subarray
 *
 * Given an integer array nums, find the subarray with the largest sum, and
 * return its sum.
 *
 * Example 1:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: The subarray [4,-1,2,1] has the largest sum 6.
 * Example 2:
 * Input: nums = [1]
 * Output: 1
 * Explanation: The subarray [1] has the largest sum 1.
 * Example 3:
 * Input: nums = [5,4,-1,7,8]
 * Output: 23
 * Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 *
 * Constraints:
 * 	1 <= nums.length <= 10^5
 * 	-10^4 <= nums[i] <= 10^4
 *
 * Follow up: If you have figured out the O(n) solution, try coding another
 * solution using the divide and conquer approach, which is more subtle.
 *
 */

// problem: https://leetcode.com/problems/maximum-subarray/
// discuss: https://leetcode.com/problems/maximum-subarray/discuss/

#include <limits>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = std::numeric_limits<int>::min();
        int current_sum = 0;

        for (auto num : nums) {
            current_sum += num;

            if (current_sum > result) {
                result = current_sum;
            }

            if (current_sum < 0) {
                current_sum = 0;
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0053, Example1) {
    Solution solution;

    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    auto result = 6;

    EXPECT_EQ(solution.maxSubArray(nums), result);
}

TEST(Problem0053, Example2) {
    Solution solution;

    vector<int> nums = {1};

    auto result = 1;

    EXPECT_EQ(solution.maxSubArray(nums), result);
}

TEST(Problem0053, Example3) {
    Solution solution;

    vector<int> nums = {5, 4, -1, 7, 8};

    auto result = 23;

    EXPECT_EQ(solution.maxSubArray(nums), result);
}

#endif
