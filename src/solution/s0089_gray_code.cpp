/**
 * File              : s0089_gray_code.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-27 20:34:39
 * Last Modified Date: 2026-11-27 21:34:56
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0089] Gray Code
 *
 * An n-bit gray code sequence is a sequence of 2^n integers where:
 * 	Every integer is in the inclusive range [0, 2^n - 1],
 * 	The first integer is 0,
 * 	An integer appears no more than once in the sequence,
 * 	The binary representation of every pair of adjacent integers differs by
 * exactly one bit, and The binary representation of the first and last integers
 * differs by exactly one bit. Given an integer n, return any valid n-bit gray
 * code sequence.
 *
 * Example 1:
 * Input: n = 2
 * Output: [0,1,3,2]
 * Explanation:
 * The binary representation of [0,1,3,2] is [00,01,11,10].
 * - 00 and 01 differ by one bit
 * - 01 and 11 differ by one bit
 * - 11 and 10 differ by one bit
 * - 10 and 00 differ by one bit
 * [0,2,3,1] is also a valid gray code sequence, whose binary representation is
 * [00,10,11,01].
 * - 00 and 10 differ by one bit
 * - 10 and 11 differ by one bit
 * - 11 and 01 differ by one bit
 * - 01 and 00 differ by one bit
 * Example 2:
 * Input: n = 1
 * Output: [0,1]
 *
 * Constraints:
 * 	1 <= n <= 16
 *
 */

// problem: https://leetcode.com/problems/gray-code/
// discuss: https://leetcode.com/problems/gray-code/discuss/

#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<int> grayCode(int n) {
        if (n == 1) {
            return {0, 1};
        }

        vector<int> gray_code_n_1 = grayCode(n - 1);
        vector<int> result = gray_code_n_1;

        int pow_n_1 = 1 << (n - 1);
        ;

        for (auto p = gray_code_n_1.rbegin(); p != gray_code_n_1.rend(); ++p) {
            result.push_back(*p + pow_n_1);
        }

        return result;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

#include <algorithm>
#include <bit>
#include <unordered_set>

bool isValidGray(const vector<int>& seq) {
    size_t len = seq.size();

    if (len == 0 || (len & (len - 1)) != 0) {
        return false;
    }

    const int n = static_cast<int>(std::countr_zero(len));
    const unsigned int mask = (1U << n) - 1U;

    unordered_set<int> s(seq.begin(), seq.end());
    if (s.size() != len) {
        return false;
    }

    bool allInRange = std::all_of(seq.begin(), seq.end(), [mask](int x) {
        return (static_cast<unsigned int>(x) & (~mask)) == 0U;
    });
    if (!allInRange) {
        return false;
    }

    auto isOneBit = [](int x) { return x != 0 && (x & (x - 1)) == 0; };

    for (size_t i = 0; i < seq.size() - 1; ++i) {
        if (!isOneBit(seq[i] ^ seq[i + 1])) {
            return false;
        }
    }

    if (!isOneBit(seq.back() ^ seq[0])) {
        return false;
    }

    return true;
}

TEST(Problem0089, InvalidGrayCodeCases) {
    EXPECT_FALSE(isValidGray({}));
    EXPECT_FALSE(isValidGray({0, 1, 2}));
    EXPECT_FALSE(isValidGray({0, 0, 1, 3}));
    EXPECT_FALSE(isValidGray({0, 1, 5, 4}));
    EXPECT_FALSE(isValidGray({0, 3, 2, 1}));
    EXPECT_FALSE(isValidGray({0, 1, 3, 0}));
    EXPECT_FALSE(isValidGray({0, 2, 3, 1, 5, 4, 6, 7}));
}

TEST(Problem0089, AllCases) {
    Solution solution;

    for (auto n = 1; n <= 16; ++n) {
        EXPECT_TRUE(isValidGray(solution.grayCode(n)));
    }
}

#endif
