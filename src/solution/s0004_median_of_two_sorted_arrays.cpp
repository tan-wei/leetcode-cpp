/**
 * File              : s0004_median_of_two_sorted_arrays.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-03 20:58:23
 * Last Modified Date: 2026-09-03 21:20:23
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0004] Median of Two Sorted Arrays
 *
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return
 * the median of the two sorted arrays. The overall run time complexity should
 * be O(log (m+n)).
 *
 * Example 1:
 * Input: nums1 = [1,3], nums2 = [2]
 * Output: 2.00000
 * Explanation: merged array = [1,2,3] and median is 2.
 * Example 2:
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 2.50000
 * Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 *
 * Constraints:
 * 	nums1.length == m
 * 	nums2.length == n
 * 	0 <= m <= 1000
 * 	0 <= n <= 1000
 * 	1 <= m + n <= 2000
 * 	-10^6 <= nums1[i], nums2[i] <= 10^6
 *
 */

// problem: https://leetcode.com/problems/median-of-two-sorted-arrays/
// discuss: https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return 0.0;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0004, Example1) {
    GTEST_SKIP();
    Solution solution;

    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};

    auto result = 2.00000f;

    EXPECT_FLOAT_EQ(solution.findMedianSortedArrays(nums1, nums2), result);
}

TEST(Problem0004, Example2) {
    GTEST_SKIP();
    Solution solution;

    vector<int> nums1 = {1, 2};
    vector<int> nums2 = {3, 4};

    auto result = 2.50000f;

    EXPECT_FLOAT_EQ(solution.findMedianSortedArrays(nums1, nums2), result);
}
#endif
