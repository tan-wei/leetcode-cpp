/**
 * File              : s0011_container_with_most_water.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-10 23:42:49
 * Last Modified Date: 2026-09-10 23:48:40
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0011] Container With Most Water
 *
 * You are given an integer array height of length n. There are n vertical lines
 * drawn such that the two endpoints of the i^th line are (i, 0) and (i,
 * height[i]). Find two lines that together with the x-axis form a container,
 * such that the container contains the most water. Return the maximum amount of
 * water a container can store. Notice that you may not slant the container.
 *
 * Example 1:
 * Input: height = [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * Explanation: The above vertical lines are represented by array
 * [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the
 * container can contain is 49.
 * Example 2: Input: height = [1,1]
 * Output: 1
 *
 * Constraints:
 * 	n == height.length
 * 	2 <= n <= 10^5
 * 	0 <= height[i] <= 10^4
 *
 */

// problem: https://leetcode.com/problems/container-with-most-water/
// discuss: https://leetcode.com/problems/container-with-most-water/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;
        int i = 0;
        int j = height.size() - 1;

        while (i < j) {
            int area =
                (j - i) * (height[i] < height[j] ? height[i] : height[j]);

            if (area > max_area) {
                max_area = area;
            }

            if (height[i] < height[j]) {
                ++i;
            } else {
                --j;
            }
        }

        return max_area;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0011, Example1) {
    Solution solution;

    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    auto result = 49;

    EXPECT_EQ(solution.maxArea(height), result);
}

TEST(Problem0011, Example2) {
    Solution solution;

    vector<int> height = {1, 1};

    auto result = 1;

    EXPECT_EQ(solution.maxArea(height), result);
}

#endif
