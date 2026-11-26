/**
 * File              : s0088_merge_sorted_array.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-26 19:09:04
 * Last Modified Date: 2026-11-26 20:10:30
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0088] Merge Sorted Array
 *
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing
 * order, and two integers m and n, representing the number of elements in nums1
 * and nums2 respectively. Merge nums1 and nums2 into a single array sorted in
 * non-decreasing order. The final sorted array should not be returned by the
 * function, but instead be stored inside the array nums1. To accommodate this,
 * nums1 has a length of m + n, where the first m elements denote the elements
 * that should be merged, and the last n elements are set to 0 and should be
 * ignored. nums2 has a length of n.
 *
 * Example 1:
 * Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 * Explanation:
 * The arrays we are merging are [1,2,3] and [2,5,6].
 * The result of the merge is [1,2,2,3,5,6] with the underlined elements coming
 * from nums1.
 * Example 2: Input: nums1 = [1], m = 1, nums2 = [], n = 0
 * Output: [1]
 * Explanation:
 * The arrays we are merging are [1] and []. The result of the
 * merge is [1].
 * Example 3:
 * Input: nums1 = [0], m = 0, nums2 = [1], n = 1
 * Output: [1]
 * Explanation:
 * The arrays we are merging are [] and [1].
 * The result of the merge is [1].
 * Note that because m = 0, there are no elements in nums1. The 0 is only there
 * to ensure the merge result can fit in nums1.
 *
 * Constraints:
 * 	nums1.length == m + n
 * 	nums2.length == n
 * 	0 <= m, n <= 200
 * 	1 <= m + n <= 200
 * 	-10^9 <= nums1[i], nums2[j] <= 10^9
 *
 * Follow up: Can you come up with an algorithm that runs in O(m + n) time?
 *
 */

// problem: https://leetcode.com/problems/merge-sorted-array/
// discuss: https://leetcode.com/problems/merge-sorted-array/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (n == 0) {
            return;
        }

        int cur_1 = m - 1;
        int cur_2 = n - 1;
        int i = m + n - 1;

        while (cur_1 >= 0 && cur_2 >= 0) {
            if (nums1[cur_1] > nums2[cur_2]) {
                nums1[i] = nums1[cur_1--];
            } else {
                nums1[i] = nums2[cur_2--];
            }
            --i;
        }

        while (cur_1 >= 0) {
            nums1[i] = nums1[cur_1--];
            --i;
        }

        while (cur_2 >= 0) {
            nums1[i] = nums2[cur_2--];
            --i;
        }
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0088, Example1) {
    Solution solution;

    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    auto m = 3;
    vector<int> nums2 = {2, 5, 6};
    auto n = 3;

    vector<int> result = {1, 2, 2, 3, 5, 6};

    solution.merge(nums1, m, nums2, n);

    EXPECT_EQ(nums1, result);
}

TEST(Problem0088, Example2) {
    Solution solution;

    vector<int> nums1 = {1};
    auto m = 1;
    vector<int> nums2 = {};
    auto n = 0;

    vector<int> result = {1};

    solution.merge(nums1, m, nums2, n);

    EXPECT_EQ(nums1, result);
}

TEST(Problem0088, Example3) {
    Solution solution;

    vector<int> nums1 = {0};
    auto m = 0;
    vector<int> nums2 = {1};
    auto n = 1;

    vector<int> result = {1};

    solution.merge(nums1, m, nums2, n);

    EXPECT_EQ(nums1, result);
}

#endif
