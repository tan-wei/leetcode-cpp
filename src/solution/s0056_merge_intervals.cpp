/**
 * File              : s0056_merge_intervals.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-25 10:51:50
 * Last Modified Date: 2026-10-25 18:30:25
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0056] Merge Intervals
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all
 * overlapping intervals, and return an array of the non-overlapping intervals
 * that cover all the intervals in the input.
 *
 * Example 1:
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 * Example 2:
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 * Example 3:
 * Input: intervals = [[4,7],[1,4]]
 * Output: [[1,7]]
 * Explanation: Intervals [1,4] and [4,7] are considered overlapping.
 *
 * Constraints:
 * 	1 <= intervals.length <= 10^4
 * 	intervals[i].length == 2
 * 	0 <= starti <= endi <= 10^4
 *
 */

// problem: https://leetcode.com/problems/merge-intervals/
// discuss: https://leetcode.com/problems/merge-intervals/discuss/

#include <algorithm>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const auto& lhs, const auto& rhs) {
                 return (lhs[0] < rhs[0]) ||
                        ((lhs[0] == rhs[0]) && (lhs[1] < rhs[1]));
             });

        vector<vector<int>> result;
        int left = 0;
        int cur = 0;

        while (cur < intervals.size()) {
            int max_end = intervals[cur][1];
            while (cur + 1 < intervals.size() &&
                   max_end >= intervals[cur + 1][0]) {
                ++cur;

                if (intervals[cur][1] > max_end) {
                    max_end = intervals[cur][1];
                }
            }
            result.push_back({intervals[left][0], max_end});
            ++cur;
            left = cur;
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0056, Example1) {
    Solution solution;

    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    vector<vector<int>> result = {{1, 6}, {8, 10}, {15, 18}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, Example2) {
    Solution solution;

    vector<vector<int>> intervals = {{1, 4}, {4, 5}};

    vector<vector<int>> result = {{1, 5}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, Example3) {
    Solution solution;

    vector<vector<int>> intervals = {{4, 7}, {1, 4}};

    vector<vector<int>> result = {{1, 7}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, SingleInterval) {
    Solution solution;

    vector<vector<int>> intervals = {{2, 5}};

    vector<vector<int>> result = {{2, 5}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, AdditionalCaseNoOverlapDiscrete) {
    Solution solution;

    vector<vector<int>> intervals = {{1, 2}, {3, 4}, {5, 6}};

    vector<vector<int>> result = {{1, 2}, {3, 4}, {5, 6}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, AdditionalCaseFullyContained) {
    Solution solution;

    vector<vector<int>> intervals = {{1, 10}, {2, 3}, {5, 7}};

    vector<vector<int>> result = {{1, 10}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, AdditionalCaseMultipleOverlapMergeOne) {
    Solution solution;

    vector<vector<int>> intervals = {{1, 3}, {2, 5}, {4, 7}, {6, 8}};

    vector<vector<int>> result = {{1, 8}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, AdditionalCaseAllSameIntervals) {
    Solution solution;

    vector<vector<int>> intervals = {{5, 7}, {5, 7}, {5, 7}};

    vector<vector<int>> result = {{5, 7}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, AdditionalCaseZeroValueInterval) {
    Solution solution;

    vector<vector<int>> intervals = {{0, 0}, {0, 2}};

    vector<vector<int>> result = {{0, 2}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, AdditionalCaseReverseOrderInput) {
    Solution solution;

    vector<vector<int>> intervals = {{10, 12}, {7, 9}, {3, 5}, {1, 2}};

    vector<vector<int>> result = {{1, 2}, {3, 5}, {7, 9}, {10, 12}};

    EXPECT_EQ(solution.merge(intervals), result);
}

TEST(Problem0056, AdditionalCaseTwoGroupOverlap) {
    Solution solution;

    vector<vector<int>> intervals = {{1, 4}, {0, 2}, {3, 5}, {7, 9}, {8, 10}};

    vector<vector<int>> result = {{0, 5}, {7, 10}};

    EXPECT_EQ(solution.merge(intervals), result);
}

#endif
