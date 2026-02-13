/**
 * File              : s0001_two_sum.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-02-13 11:24:19
 * Last Modified Date: 2026-02-13 11:40:09
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/**
 * [0001] Two Sum
 *
 * Given an array of integers nums and an integer target, return indices of the
 * two numbers such that they add up to target. You may assume that each input
 * would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 * Example 3:
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 * Constraints:
 * 	2 <= nums.length <= 10^4
 * 	-10^9 <= nums[i] <= 10^9
 * 	-10^9 <= target <= 10^9
 * 	Only one valid answer exists.
 *
 * Follow-up: Can you come up with an algorithm that is less than O(n^2)<font
 * face="monospace"> </font>time complexity?
 */

// problem: https://leetcode.com/problems/two-sum/
// discuss: https://leetcode.com/problems/two-sum/discuss/

using namespace std;

// submission codes start here

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> lookup_map;

        for (int i = 0; i < nums.size(); ++i) {
            if (lookup_map.count(target - nums[i])) {
                return {lookup_map[target - nums[i]], i};
            }
            lookup_map[nums[i]] = i;
        }

        return vector<int>{};
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0001, Example1) {
    Solution solution;

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = {0, 1};

    ASSERT_EQ(solution.twoSum(nums, target), result);
}

TEST(Problem0001, Example2) {
    Solution solution;

    vector<int> nums = {3, 2, 4};
    int target = 6;
    vector<int> result = {1, 2};

    ASSERT_EQ(solution.twoSum(nums, target), result);
}

TEST(Problem0001, Example3) {
    Solution solution;

    vector<int> nums = {3, 3};
    int target = 6;
    vector<int> result = {0, 1};

    ASSERT_EQ(solution.twoSum(nums, target), result);
}

#endif
