/**
 * File              : s0026_remove_duplicates_from_sorted_array.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-25 17:55:01
 * Last Modified Date: 2026-09-25 21:28:35
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0026] Remove Duplicates from Sorted Array
 *
 * Given an integer array nums sorted in non-decreasing order, remove the
 * duplicates in-place such that each unique element appears only once. The
 * relative order of the elements should be kept the same. Consider the number
 * of unique elements in nums to be k​​​​​​​​​​​​​​.
 * After removing duplicates, return the number of unique elements k. The first
 * k elements of nums should contain the unique numbers in sorted order. The
 * remaining elements beyond index k - 1 can be ignored. Custom Judge: The judge
 * will test your solution with the following code: int[] nums = [...]; // Input
 * array int[] expectedNums = [...]; // The expected answer with correct length
 * int k = removeDuplicates(nums); // Calls your implementation
 * assert k == expectedNums.length;
 * for (int i = 0; i < k; i++) {
 *     assert nums[i] == expectedNums[i];
 * }
 * If all assertions pass, then your solution will be accepted.
 *
 * Example 1:
 * Input: nums = [1,1,2]
 * Output: 2, nums = [1,2,_]
 * Explanation: Your function should return k = 2, with the first two elements
 * of nums being 1 and 2 respectively. It does not matter what you leave beyond
 * the returned k (hence they are underscores).
 * Example 2:
 * Input: nums = [0,0,1,1,1,2,2,3,3,4]
 * Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
 * Explanation: Your function should return k = 5, with the first five elements
 * of nums being 0, 1, 2, 3, and 4 respectively. It does not matter what you
 * leave beyond the returned k (hence they are underscores).
 *
 * Constraints:
 * 	1 <= nums.length <= 3 * 10^4
 * 	-100 <= nums[i] <= 100
 * 	nums is sorted in non-decreasing order.
 *
 */

// problem: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// discuss:
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        auto size = nums.size();

        if (size <= 1) {
            return size;
        }
        auto cur = 1;

        for (auto i = 1; i < size; i++) {
            if (nums[i - 1] != nums[i]) {
                nums[cur] = nums[i];
                cur++;
            }
        }

        return cur;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0026, Example1) {
    Solution solution;

    vector<int> nums = {1, 1, 2};

    vector<int> result = {1, 2};

    EXPECT_EQ(solution.removeDuplicates(nums), result.size());
    EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
              vector<int>(result.begin(), result.begin() + result.size()));
}

TEST(Problem0026, Example2) {
    Solution solution;

    vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    vector<int> result = {0, 1, 2, 3, 4};

    EXPECT_EQ(solution.removeDuplicates(nums), result.size());
    EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
              vector<int>(result.begin(), result.begin() + result.size()));
}

TEST(Problem0026, AdditionalCaseSingleElement) {
    Solution solution;

    vector<int> nums = {1};

    vector<int> result = {1};

    EXPECT_EQ(solution.removeDuplicates(nums), result.size());
    EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
              vector<int>(result.begin(), result.begin() + result.size()));
}

TEST(Problem0026, AdditionalCaseAllDuplicates) {
    Solution solution;

    vector<int> nums = {2, 2, 2, 2, 2};

    vector<int> result = {2};

    EXPECT_EQ(solution.removeDuplicates(nums), result.size());
    EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
              vector<int>(result.begin(), result.begin() + result.size()));
}

TEST(Problem0026, AdditionalCaseNoDuplicates) {
    Solution solution;

    vector<int> nums = {1, 2, 3, 4, 5};

    vector<int> result = {1, 2, 3, 4, 5};

    EXPECT_EQ(solution.removeDuplicates(nums), result.size());
    EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
              vector<int>(result.begin(), result.begin() + result.size()));
}

TEST(Problem0026, AdditionalCaseNegativeNumbers) {
    Solution solution;

    vector<int> nums = {-3, -3, -1, 0, 0, 0, 2, 2};

    vector<int> result = {-3, -1, 0, 2};

    EXPECT_EQ(solution.removeDuplicates(nums), result.size());
    EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
              vector<int>(result.begin(), result.begin() + result.size()));
}

#endif
