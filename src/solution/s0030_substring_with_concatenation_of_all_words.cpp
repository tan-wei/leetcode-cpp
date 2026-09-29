/**
 * File              : s0030_substring_with_concatenation_of_all_words.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-29 18:48:43
 * Last Modified Date: 2026-09-29 20:21:52
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0030] Substring with Concatenation of All Words
 *
 * You are given a string s and an array of strings words. All the strings of
 * words are of the same length. A concatenated string is a string that exactly
 * contains all the strings of any permutation of words concatenated. For
 * example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef",
 * "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is
 * not a concatenated string because it is not the concatenation of any
 * permutation of words. Return an array of the starting indices of all the
 * concatenated substrings in s. You can return the answer in any order.
 *
 * Example 1:
 * Input: s = "barfoothefoobarman", words = ["foo","bar"]
 * Output: [0,9]
 * Explanation:
 * The substring starting at 0 is "barfoo". It is the concatenation of
 * ["bar","foo"] which is a permutation of words. The substring starting at 9 is
 * "foobar". It is the concatenation of ["foo","bar"] which is a permutation of
 * words.
 * Example 2:
 * Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
 * Output: []
 * Explanation: There is no concatenated substring.
 * Example 3:
 * Input: s = "barfoofoobarthefoobarman",
 * words = ["bar","foo","the"]
 * Output: [6,9,12]
 * Explanation:
 * The substring starting at 6 is "foobarthe". It is the
 * concatenation of ["foo","bar","the"]. The substring starting at 9 is
 * "barthefoo". It is the concatenation of
 * ["bar","the","foo"]. The substring starting at 12 is "thefoobar". It is the
 * concatenation of ["the","foo","bar"].
 *
 * Constraints:
 * 	1 <= s.length <= 10^4
 * 	1 <= words.length <= 5000
 * 	1 <= words[i].length <= 30
 * 	s and words[i] consist of lowercase English letters.
 *
 */

// problem:
// https://leetcode.com/problems/substring-with-concatenation-of-all-words/
// discuss:
// https://leetcode.com/problems/substring-with-concatenation-of-all-words/discuss/

#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    vector<int> findSubstring(string s, vector<string>& words) { return {}; }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0030, Example1) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = "barfoothefoobarman"s;
    vector<string> words = {"foo", "bar"};

    vector<int> result = {0, 9};

    EXPECT_EQ(solution.findSubstring(s, words), result);
}

TEST(Problem0030, Example2) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = "barfoothefoobarman"s;
    vector<string> words = {"foo", "bar"};

    vector<int> result = {0, 9};

    EXPECT_EQ(solution.findSubstring(s, words), result);
}

TEST(Problem0030, Example3) {
    GTEST_SKIP() << "Hard one, skip";
    Solution solution;

    auto s = "barfoothefoobarman"s;
    vector<string> words = {"bar", "foo", "the"};

    vector<int> result = {6, 9, 12};

    EXPECT_EQ(solution.findSubstring(s, words), result);
}

#endif
