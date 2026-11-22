/**
 * File              : s0084_largest_rectangle_in_histogram.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-22 14:28:58
 * Last Modified Date: 2026-11-22 14:37:05
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0084] Largest Rectangle in Histogram
 *
 * Given an array of integers heights representing the histogram's bar height
 * where the width of each bar is 1, return the area of the largest rectangle in
 * the histogram.
 *
 * Example 1:
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10
 * Explanation: The above is a histogram where width of each bar is 1.
 * The largest rectangle is shown in the red area, which has an area = 10 units.
 * Example 2:
 * Input: heights = [2,4]
 * Output: 4
 *
 * Constraints:
 * 	1 <= heights.length <= 10^5
 * 	0 <= heights[i] <= 10^4
 *
 */

// problem: https://leetcode.com/problems/largest-rectangle-in-histogram/
// discuss:
// https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;

        heights.push_back(0);
        vector<int> index;

        for (int i = 0; i < heights.size(); i++) {
            while (index.size() > 0 && heights[index.back()] >= heights[i]) {
                int h = heights[index.back()];
                index.pop_back();

                int sidx = index.size() > 0 ? index.back() : -1;
                if (h * (i - sidx - 1) > result) {
                    result = h * (i - sidx - 1);
                }
            }

            index.push_back(i);
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0084, Example1) {
    Solution solution;

    vector<int> heights = {2, 1, 5, 6, 2, 3};

    auto result = 10;

    EXPECT_EQ(solution.largestRectangleArea(heights), result);
}

TEST(Problem0084, Example2) {
    Solution solution;

    vector<int> heights = {2, 4};

    auto result = 4;

    EXPECT_EQ(solution.largestRectangleArea(heights), result);
}

#endif
