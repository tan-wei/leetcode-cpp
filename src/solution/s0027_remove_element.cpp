/**
 * File              : s0027_remove_element.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-26 11:39:56
 * Last Modified Date: 2026-09-26 19:57:28
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0027] Remove Element
 *
 * Given an integer array nums and an integer val, remove all occurrences of val
 * in nums in-place. The order of the elements may be changed. Then return the
 * number of elements in nums which are not equal to val. Consider the number of
 * elements in nums which are not equal to val be k, to get accepted, you need
 * to do the following things: Change the array nums such that the first k
 * elements of nums contain the elements which are not equal to val. The
 * remaining elements of nums are not important as well as the size of nums.
 * 	Return k.
 * Custom Judge:
 * The judge will test your solution with the following code:
 * int[] nums = [...]; // Input array
 * int val = ...; // Value to remove
 * int[] expectedNums = [...]; // The expected answer with correct length.
 *                             // It is sorted with no values equaling val.
 * int k = removeElement(nums, val); // Calls your implementation
 * assert k == expectedNums.length;
 * sort(nums, 0, k); // Sort the first k elements of nums
 * for (int i = 0; i < actualLength; i++) {
 *     assert nums[i] == expectedNums[i];
 *
 * If all assertions pass, then your solution will be accepted.
 *
 * Example 1:
 * Input: nums = [3,2,2,3], val = 3
 * Output: 2, nums = [2,2,_,_]
 * Explanation: Your function should return k = 2, with the first two elements
 * of nums being 2. It does not matter what you leave beyond the returned k
 * (hence they are underscores). Example 2: Input: nums = [0,1,2,2,3,0,4,2], val
 * = 2 Output: 5, nums = [0,1,4,0,3,_,_,_] Explanation: Your function should
 * return k = 5, with the first five elements of nums containing 0, 0, 1, 3,
 * and 4. Note that the five elements can be returned in any order. It does not
 * matter what you leave beyond the returned k (hence they are underscores).
 *
 * Constraints:
 * 	0 <= nums.length <= 100
 * 	0 <= nums[i] <= 50
 * 	0 <= val <= 100
 *
 */

// problem: https://leetcode.com/problems/remove-element/
// discuss: https://leetcode.com/problems/remove-element/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        auto cur = 0;

        for (auto i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[cur] = nums[i];
                cur++;
            }
        }

        return cur;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0027, Example1) {
    Solution solution;

    vector<int> nums = {3, 2, 2, 3};
    auto val = 3;

    vector<int> result = {2, 2};

    EXPECT_EQ(solution.removeElement(nums, val), result.size());
    EXPECT_THAT(vector<int>(nums.begin(), nums.begin() + result.size()),
                ::testing::UnorderedElementsAreArray(vector<int>(
                    result.begin(), result.begin() + result.size())));
    // EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
    //           vector<int>(result.begin(), result.begin() + result.size()));
}

TEST(Problem0027, Example2) {
    Solution solution;

    vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    auto val = 2;

    vector<int> result = {0, 1, 4, 0, 3};

    EXPECT_EQ(solution.removeElement(nums, val), result.size());
    EXPECT_THAT(vector<int>(nums.begin(), nums.begin() + result.size()),
                ::testing::UnorderedElementsAreArray(vector<int>(
                    result.begin(), result.begin() + result.size())));
    // EXPECT_EQ(vector<int>(nums.begin(), nums.begin() + result.size()),
    //           vector<int>(result.begin(), result.begin() + result.size()));
}

#endif
