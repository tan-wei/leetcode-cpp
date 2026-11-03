/**
 * File              : s0065_valid_number.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-03 21:06:39
 * Last Modified Date: 2026-11-03 21:20:29
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0065] Valid Number
 *
 * Given a string s, return whether s is a valid number.
 * For example, all the following are valid numbers: "2", "0089", "-0.1",
 * "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93",
 * "-123.456e789", while the following are not valid numbers: "abc", "1a", "1e",
 * "e3", "99e2.5", "--6", "-+3", "95a54e53". Formally, a valid number is defined
 * using one of the following definitions: An integer number followed by an
 * optional exponent. A decimal number followed by an optional exponent. An
 * integer number is defined with an optional sign '-' or '+' followed by
 * digits. A decimal number is defined with an optional sign '-' or '+' followed
 * by one of the following definitions: Digits followed by a dot '.'. Digits
 * followed by a dot '.' followed by digits. A dot '.' followed by digits. An
 * exponent is defined with an exponent notation 'e' or 'E' followed by an
 * integer number. The digits are defined as one or more digits.
 *
 * Example 1:
 * Input: s = "0"
 * Output: true
 * Example 2:
 * Input: s = "e"
 * Output: false
 * Example 3:
 * Input: s = "."
 * Output: false
 *
 * Constraints:
 * 	1 <= s.length <= 20
 * 	s consists of only English letters (both uppercase and lowercase), digits
 * (0-9), plus '+', minus '-', or dot '.'.
 *
 */

// problem: https://leetcode.com/problems/valid-number/
// discuss: https://leetcode.com/problems/valid-number/discuss/

#include <string>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    bool isNumber(string s) {
        auto result = false;
        auto exp = false;
        auto sign = false;
        auto dec = false;
        for (int i = 0, n = s.length(); i < n; ++i) {
            const char& ch = s[i];
            if (isdigit(ch)) {
                result = true;
            } else if (ch == 'e' || ch == 'E') {
                if (exp || !result) {
                    return false;
                } else {
                    exp = true, result = false, sign = false, dec = false;
                }
            } else if (ch == '+' || ch == '-') {
                if (sign || result || dec) {
                    return false;
                } else {
                    sign = true;
                }
            } else if (ch == '.') {
                if (dec || exp) {
                    return false;
                } else {
                    dec = true;
                }
            } else {
                return false;
            }
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0065, Example1) {
    Solution solution;

    auto s = "0"s;

    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, Example2) {
    Solution solution;

    auto s = "e"s;

    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, Example3) {
    Solution solution;

    auto s = "."s;

    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidIntegerSingleDigit) {
    Solution solution;

    auto s = "2"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidIntegerLeadingZeros) {
    Solution solution;

    auto s = "0089"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidNegativeDecimal) {
    Solution solution;

    auto s = "-0.1"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidPositiveDecimalWithSign) {
    Solution solution;

    auto s = "+3.14"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidDecimalEndingWithDot) {
    Solution solution;

    auto s = "4."s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidDecimalStartingWithDotAndSign) {
    Solution solution;

    auto s = "-.9"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidScientificNotationLowercase) {
    Solution solution;

    auto s = "2e10"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065,
     AdditionalCasealidScientificNotationUppercaseWithNegativeSign) {
    Solution solution;

    auto s = "-90E3"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidScientificNotationWithExponentSign) {
    Solution solution;

    auto s = "3e+7"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065,
     AdditionalCasealidScientificNotationWithBaseSignAndNegativeExponent) {
    Solution solution;

    auto s = "+6e-1"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidComplexDecimalAndExponent) {
    Solution solution;

    auto s = "53.5e93"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasealidLongDecimalAndLargeExponent) {
    Solution solution;

    auto s = "-123.456e789"s;
    auto result = true;

    EXPECT_EQ(solution.isNumber(s), result);
}

// --- 非法数字测试用例 ---

TEST(Problem0065, AdditionalCasenvalidAlphabeticString) {
    Solution solution;

    auto s = "abc"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidNumberWithTrailingLetter) {
    Solution solution;

    auto s = "1a"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidIncompleteExponent1) {
    Solution solution;

    auto s = "1e"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidIncompleteExponent2) {
    Solution solution;

    auto s = "e3"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidDecimalExponent) {
    Solution solution;

    auto s = "99e2.5"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidDoubleSigns) {
    Solution solution;

    auto s = "--6"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidConflictingSigns) {
    Solution solution;

    auto s = "-+3"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidEmbeddedLetters) {
    Solution solution;

    auto s = "95a54e53"s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

TEST(Problem0065, AdditionalCasenvalidMultipleDots) {
    Solution solution;

    auto s = ".."s;
    auto result = false;

    EXPECT_EQ(solution.isNumber(s), result);
}

#endif
