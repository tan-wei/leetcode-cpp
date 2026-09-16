/**
 * File              : s0017_letter_combinations_of_a_phone_number.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-09-16 20:01:14
 * Last Modified Date: 2026-09-16 20:39:07
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0017] Letter Combinations of a Phone Number
 *
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent. Return the answer in any
 * order. A mapping of digits to letters (just like on the telephone buttons) is
 * given below. Note that 1 does not map to any letters.
 *
 * Example 1:
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 * Example 2:
 * Input: digits = "2"
 * Output: ["a","b","c"]
 *
 * Constraints:
 * 	1 <= digits.length <= 4
 * 	digits[i] is a digit in the range ['2', '9'].
 *
 */

// problem: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// discuss:
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/discuss/

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    vector<string> letterCombinations(string digits) {
        if (digits.length() == 0) {
            return {};
        }

        static const vector<string> digit_to_char = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        vector<string> result{""};

        for (auto d : digits) {
            if (d >= '0' && d <= '9') {
                auto chars = digit_to_char[d - '0'];
                vector<string> tmp;
                for (auto c : chars) {
                    transform(result.cbegin(), result.cend(),
                              back_inserter(tmp),
                              [c](const auto& s) { return s + c; });
                }
                result.swap(tmp);
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

TEST(Problem0017, Example1) {
    Solution solution;

    auto digits = "23"s;

    vector<string> result = {
        "ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};

    EXPECT_THAT(solution.letterCombinations(digits),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0017, Example2) {
    Solution solution;

    auto digits = "2"s;

    vector<string> result = {"a", "b", "c"};

    EXPECT_THAT(solution.letterCombinations(digits),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0017, AdditionalCaseEmptyDigits) {
    Solution solution;

    auto digits = ""s;

    vector<string> result = {};

    EXPECT_EQ(solution.letterCombinations(digits), result);
}

TEST(Problem0017, AdditionalCaseDigitsWithFourLetters) {
    Solution solution;

    auto digits = "7"s;

    vector<string> result = {"p", "q", "r", "s"};

    EXPECT_THAT(solution.letterCombinations(digits),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0017, AdditionalCaseSameDigitsRepeated) {
    Solution solution;

    auto digits = "22"s;

    vector<string> result = {
        "aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"};

    EXPECT_THAT(solution.letterCombinations(digits),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0017, AdditionalCaseMixedThreeAndFourLetterDigits) {
    Solution solution;

    auto digits = "27"s;

    vector<string> result = {
        "ap", "aq", "ar", "as", "bp", "bq", "br", "bs", "cp", "cq", "cr", "cs"};

    EXPECT_THAT(solution.letterCombinations(digits),
                ::testing::UnorderedElementsAreArray(result));
}

TEST(Problem0017, AdditionalCaseMaxConstraintLengthFourDigits) {
    Solution solution;

    auto digits = "2345"s;

    // 3 * 3 * 3 * 3 = 81 combinations
    auto actual = solution.letterCombinations(digits);

    EXPECT_EQ(actual.size(), 81);

    // Sample some to check
    EXPECT_THAT(actual, ::testing::Contains("adgj"));
    EXPECT_THAT(actual, ::testing::Contains("cfil"));
}

#endif
