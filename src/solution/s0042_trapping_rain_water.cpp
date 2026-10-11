/**
 * File              : s0042_trapping_rain_water.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-11 13:47:08
 * Last Modified Date: 2026-10-11 13:56:42
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0042] Trapping Rain Water
 *
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 *
 * Example 1:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by array
 * [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section)
 * are being trapped.
 * Example 2:
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 *
 * Constraints:
 * 	n == height.length
 * 	1 <= n <= 2 * 10^4
 * 	0 <= height[i] <= 10^5
 *
 */

// problem: https://leetcode.com/problems/trapping-rain-water/
// discuss: https://leetcode.com/problems/trapping-rain-water/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int trap(vector<int>& height) {
        int result = 0;

        int left = 0;
        int right = height.size() - 1;

        int left_max = 0;
        int right_max = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                // left part can be counted
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    result += (left_max - height[left]);
                }

                left++;

            } else {
                // right part can be counted
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    result += (right_max - height[right]);
                }

                right--;
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0042, Example1) {
    Solution solution;

    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    auto result = 6;

    EXPECT_EQ(solution.trap(height), result);
}

TEST(Problem0042, Example2) {
    Solution solution;

    vector<int> height = {4, 2, 0, 3, 2, 5};

    auto result = 9;

    EXPECT_EQ(solution.trap(height), result);
}

#endif
