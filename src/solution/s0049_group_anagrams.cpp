/**
 * File              : s0049_group_anagrams.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-10-18 09:18:40
 * Last Modified Date: 2026-10-26 13:11:51
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0049] Group Anagrams
 *
 * Given an array of strings strs, group the anagrams together. You can return
 * the answer in any order.
 *
 * Example 1:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 * Explanation:
 * 	There is no string in strs that can be rearranged to form "bat".
 * 	The strings "nat" and "tan" are anagrams as they can be rearranged to form
 * each other. The strings "ate", "eat", and "tea" are anagrams as they can be
 * rearranged to form each other. Example 2: Input: strs = [""] Output: [[""]]
 * Example 3:
 * Input: strs = ["a"]
 * Output: [["a"]]
 *
 * Constraints:
 * 	1 <= strs.length <= 10^4
 * 	0 <= strs[i].length <= 100
 * 	strs[i] consists of lowercase English letters.
 *
 */

// problem: https://leetcode.com/problems/group-anagrams/
// discuss: https://leetcode.com/problems/group-anagrams/discuss/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, int> char_map;
        int index = 0;

        for (auto str : strs) {
            string o_str = str;
            sort(str.begin(), str.end());
            if (!char_map.contains(str)) {
                char_map[str] = index;
                result.emplace_back(vector<string>{});
                result[index].push_back(o_str);
                index++;
            } else {
                result[char_map[str]].emplace_back(o_str);
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <tuple>

TEST(Problem0049, Example1) {
    Solution solution;

    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

    vector<vector<string>> result = {
        {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};

    EXPECT_THAT(
        solution.groupAnagrams(strs),
        ::testing::UnorderedPointwise(
            ::testing::Truly([](const auto& groups) {
                return ::testing::Matches(::testing::UnorderedElementsAreArray(
                    std::get<1>(groups)))(std::get<0>(groups));
            }),
            result));
}

TEST(Problem0049, Example2) {
    Solution solution;

    vector<string> strs = {""};

    vector<vector<string>> result = {{""}};

    EXPECT_THAT(
        solution.groupAnagrams(strs),
        ::testing::UnorderedPointwise(
            ::testing::Truly([](const auto& groups) {
                return ::testing::Matches(::testing::UnorderedElementsAreArray(
                    std::get<1>(groups)))(std::get<0>(groups));
            }),
            result));
}

TEST(Problem0049, Example3) {
    Solution solution;

    vector<string> strs = {"a"};

    vector<vector<string>> result = {{"a"}};

    EXPECT_THAT(
        solution.groupAnagrams(strs),
        ::testing::UnorderedPointwise(
            ::testing::Truly([](const auto& groups) {
                return ::testing::Matches(::testing::UnorderedElementsAreArray(
                    std::get<1>(groups)))(std::get<0>(groups));
            }),
            result));
}

#endif
