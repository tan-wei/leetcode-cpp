/**
 * File              : s0031_next_permutation.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-30 18:48:55
 * Last Modified Date: 2026-09-30 22:29:32
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0031] Next Permutation
 *
 * A permutation of an array of integers is an arrangement of its members into a
 * sequence or linear order. For example, for arr = [1,2,3], the following are
 * all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2],
 * [3,2,1]. The next permutation of an array of integers is the next
 * lexicographically greater permutation of its integer. More formally, if all
 * the permutations of the array are sorted in one container according to their
 * lexicographical order, then the next permutation of that array is the
 * permutation that follows it in the sorted container. If such arrangement is
 * not possible, the array must be rearranged as the lowest possible order
 * (i.e., sorted in ascending order). For example, the next permutation of arr =
 * [1,2,3] is [1,3,2]. Similarly, the next permutation of arr = [2,3,1] is
 * [3,1,2]. While the next permutation of arr = [3,2,1] is [1,2,3] because
 * [3,2,1] does not have a lexicographical larger rearrangement. Given an array
 * of integers nums, find the next permutation of nums. The replacement must be
 * in place and use only constant extra memory.
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [1,3,2]
 * Example 2:
 * Input: nums = [3,2,1]
 * Output: [1,2,3]
 * Example 3:
 * Input: nums = [1,1,5]
 * Output: [1,5,1]
 *
 * Constraints:
 * 	1 <= nums.length <= 100
 * 	0 <= nums[i] <= 100
 *
 */

// problem: https://leetcode.com/problems/next-permutation/
// discuss: https://leetcode.com/problems/next-permutation/discuss/

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();

        int idx = -1;

        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        auto it =
            find_if(nums.rbegin(), nums.rend(),
                    [target = nums[idx]](int val) { return val > target; });

        swap(*it, nums[idx]);

        reverse(nums.begin() + idx + 1, nums.end());
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0031, Example1) {
    Solution solution;

    vector<int> nums = {1, 2, 3};

    vector<int> result = {1, 3, 2};

    solution.nextPermutation(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0031, Example2) {
    Solution solution;

    vector<int> nums = {3, 2, 1};

    vector<int> result = {1, 2, 3};

    solution.nextPermutation(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0031, Example3) {
    Solution solution;

    vector<int> nums = {1, 1, 5};

    vector<int> result = {1, 5, 1};

    solution.nextPermutation(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0031, AdditionalCaseSingleElement) {
    Solution solution;

    vector<int> nums = {1};

    vector<int> result = {1};

    solution.nextPermutation(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0031, AdditionalCaseDuplicateElements) {
    Solution solution;

    vector<int> nums = {1, 5, 1};

    vector<int> result = {5, 1, 1};

    solution.nextPermutation(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0031, AdditionalCaseComplexPermutation) {
    Solution solution;

    vector<int> nums = {1, 2, 7, 4, 3, 1};

    vector<int> result = {1, 3, 1, 2, 4, 7};

    solution.nextPermutation(nums);

    EXPECT_EQ(nums, result);
}

TEST(Problem0031, AdditionalCaseAllSameElements) {
    Solution solution;

    vector<int> nums = {2, 2, 2};

    vector<int> result = {2, 2, 2};

    solution.nextPermutation(nums);

    EXPECT_EQ(nums, result);
}

#endif
