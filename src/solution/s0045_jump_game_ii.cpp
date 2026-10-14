/**
 * File              : s0045_jump_game_ii.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-14 20:07:30
 * Last Modified Date: 2026-10-14 21:23:14
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0045] Jump Game II
 *
 * You are given a 0-indexed array of integers nums of length n. You are
 * initially positioned at index 0. Each element nums[i] represents the maximum
 * length of a forward jump from index i. In other words, if you are at index i,
 * you can jump to any index (i + j) where: 0 <= j <= nums[i] and i + j < n
 * Return the minimum number of jumps to reach index n - 1. The test cases are
 * generated such that you can reach index n - 1.
 *
 * Example 1:
 * Input: nums = [2,3,1,1,4]
 * Output: 2
 * Explanation: The minimum number of jumps to reach the last index is 2. Jump 1
 * step from index 0 to 1, then 3 steps to the last index.
 * Example 2:
 * Input: nums = [2,3,0,1,4]
 * Output: 2
 *
 * Constraints:
 * 	1 <= nums.length <= 10^4
 * 	0 <= nums[i] <= 1000
 * 	It's guaranteed that you can reach nums[n - 1].
 *
 */

// problem: https://leetcode.com/problems/jump-game-ii/
// discuss: https://leetcode.com/problems/jump-game-ii/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int jump(vector<int>& nums) {
        int start = 0;
        int end = 0;
        int terminal = nums.size() - 1;
        int move_count = 0;
        int max_end = 0;

        while (start < terminal) {
            ++move_count;
            for (int j = start; j <= end; j++) {
                if (j + nums[j] > max_end) {
                    max_end = j + nums[j];
                    if (max_end >= terminal) {
                        return move_count;
                    }
                }
            }

            start = end + 1;
            end = max_end;
        }
        return move_count;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0045, Example1) {
    Solution solution;

    vector<int> nums = {2, 3, 1, 1, 4};

    auto result = 2;

    EXPECT_EQ(solution.jump(nums), result);
}

TEST(Problem0045, Example2) {
    Solution solution;

    vector<int> nums = {2, 3, 0, 1, 4};

    auto result = 2;

    EXPECT_EQ(solution.jump(nums), result);
}

#endif
