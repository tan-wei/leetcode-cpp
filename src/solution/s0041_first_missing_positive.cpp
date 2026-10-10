/**
 * File              : s0041_first_missing_positive.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-10 14:25:10
 * Last Modified Date: 2026-10-10 14:36:22
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0041] First Missing Positive
 *
 * Given an unsorted integer array nums. Return the smallest positive integer
 * that is not present in nums. You must implement an algorithm that runs in
 * O(n) time and uses O(1) auxiliary space.
 *
 * Example 1:
 * Input: nums = [1,2,0]
 * Output: 3
 * Explanation: The numbers in the range [1,2] are all in the array.
 * Example 2:
 * Input: nums = [3,4,-1,1]
 * Output: 2
 * Explanation: 1 is in the array but 2 is missing.
 * Example 3:
 * Input: nums = [7,8,9,11,12]
 * Output: 1
 * Explanation: The smallest positive integer 1 is missing.
 *
 * Constraints:
 * 	1 <= nums.length <= 10^5
 * 	-2^31 <= nums[i] <= 2^31 - 1
 *
 */

// problem: https://leetcode.com/problems/first-missing-positive/
// discuss: https://leetcode.com/problems/first-missing-positive/discuss/

#include <utility>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            while (
                nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0041, Example1) {
    Solution solution;

    vector<int> nums = {1, 2, 0};

    auto result = 3;

    EXPECT_EQ(solution.firstMissingPositive(nums), result);
}

TEST(Problem0041, Example2) {
    Solution solution;

    vector<int> nums = {3, 4, -1, 1};

    auto result = 2;

    EXPECT_EQ(solution.firstMissingPositive(nums), result);
}

TEST(Problem0041, Example3) {
    Solution solution;

    vector<int> nums = {7, 8, 9, 11, 12};

    auto result = 1;

    EXPECT_EQ(solution.firstMissingPositive(nums), result);
}

#endif
