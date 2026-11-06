/**
 * File              : s0068_text_justification.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-06 20:47:25
 * Last Modified Date: 2026-11-06 22:28:35
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0068] Text Justification
 *
 * Given an array of strings words and a width maxWidth, format the text such
 * that each line has exactly maxWidth characters and is fully (left and right)
 * justified. You should pack your words in a greedy approach; that is, pack as
 * many words as you can in each line. Pad extra spaces ' ' when necessary so
 * that each line has exactly maxWidth characters. Extra spaces between words
 * should be distributed as evenly as possible. If the number of spaces on a
 * line does not divide evenly between words, the empty slots on the left will
 * be assigned more spaces than the slots on the right. For the last line of
 * text, it should be left-justified, and no extra space is inserted between
 * words. Note: A word is defined as a character sequence consisting of
 * non-space characters only. Each word's length is guaranteed to be greater
 * than 0 and not exceed maxWidth. The input array words contains at least one
 * word.
 *
 * Example 1:
 * Input: words = ["This", "is", "an", "example", "of", "text",
 * "justification."], maxWidth = 16
 * Output:
 * [
 *    "This    is    an",
 *    "example  of text",
 *    "justification.  "
 * ]
 * Example 2:
 * Input: words = ["What","must","be","acknowledgment","shall","be"],
 * maxWidth = 16
 * Output:
 * [
 *   "What   must   be",
 *   "acknowledgment  ",
 *   "shall be        "
 * ]
 * Explanation: Note that the last line is "shall be    " instead of "shall be",
 * because the last line must be left-justified instead of fully-justified. Note
 * that the second line is also left-justified because it contains only one
 * word.
 * Example 3: Input: words =
 * ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"],
 * maxWidth = 20
 * Output:
 * [
 *   "Science  is  what we",
 *   "understand      well",
 *   "enough to explain to",
 *   "a  computer.  Art is",
 *   "everything  else  we",
 *   "do                  "
 * ]
 *
 * Constraints:
 * 	1 <= words.length <= 300
 * 	1 <= words[i].length <= 20
 * 	words[i] consists of only English letters and symbols.
 * 	1 <= maxWidth <= 100
 * 	words[i].length <= maxWidth
 *
 */

// problem: https://leetcode.com/problems/text-justification/
// discuss: https://leetcode.com/problems/text-justification/discuss/

#include <numeric>
#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        vector<string> words_in_a_line;

        for (int i = 0; i < words.size(); ++i) {
            words_in_a_line.push_back(words[i]);
            if (isLineFull(words_in_a_line, maxWidth)) {
                words_in_a_line.pop_back();
                result.push_back(lineJustify(words_in_a_line, maxWidth));
                words_in_a_line.clear();
                words_in_a_line.push_back(words[i]);
            }
        }

        if (!words_in_a_line.empty()) {
            result.push_back(leftJustify(words_in_a_line, maxWidth));
        }

        return result;
    }

private:
    string lineJustify(const vector<string>& words, int maxWidth) {
        if (words.size() == 1) {
            return leftJustify(words, maxWidth);
        }

        int words_count = accumulate(
            words.begin(), words.end(), 0, [](int sum, const string& w) {
                return sum + static_cast<int>(w.size());
            });
        int spaces = maxWidth - words_count;
        int spaces_per_word = spaces / (static_cast<int>(words.size()) - 1);
        int extra_space = spaces % (static_cast<int>(words.size()) - 1);

        string line;
        for (int i = 0; i < static_cast<int>(words.size()) - 1; ++i) {
            if (i < extra_space) {
                line += words[i] + string(1 + spaces_per_word, ' ');
            } else {
                line += words[i] + string(spaces_per_word, ' ');
            }
        }
        line += words.back();

        return line;
    }

    string leftJustify(const vector<string>& words, int maxWidth) {
        string line;
        for (int i = 0; i < static_cast<int>(words.size()) - 1; ++i) {
            line += words[i] + ' ';
        }
        line += words.back();

        if (static_cast<int>(line.length()) < maxWidth) {
            line += string(maxWidth - static_cast<int>(line.length()), ' ');
        }
        return line;
    }

    bool isLineFull(const vector<string>& words, int maxWidth) {
        int words_length = accumulate(
            words.begin(), words.end(), 0, [](int sum, const string& w) {
                return sum + static_cast<int>(w.size());
            });
        int required = words_length + (static_cast<int>(words.size()) - 1);
        return required > maxWidth;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0068, Example1) {
    Solution solution;

    vector<string> words = {
        "This", "is", "an", "example", "of", "text", "justification."};
    auto maxWidth = 16;

    vector<string> result = {
        "This    is    an", "example  of text", "justification.  "};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, Example2) {
    Solution solution;

    vector<string> words = {
        "What", "must", "be", "acknowledgment", "shall", "be"};
    auto maxWidth = 16;

    vector<string> result = {
        "What   must   be", "acknowledgment  ", "shall be        "};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, Example3) {
    Solution solution;

    vector<string> words = {
        "Science", "is", "what",       "we",   "understand", "well",
        "enough",  "to", "explain",    "to",   "a",          "computer.",
        "Art",     "is", "everything", "else", "we",         "do"};
    auto maxWidth = 20;

    vector<string> result = {
        "Science  is  what we", "understand      well", "enough to explain to",
        "a  computer.  Art is", "everything  else  we", "do                  "};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, AdditionalCaseSingleWordExactWidth) {
    Solution solution;

    vector<string> words = {"Hello"};
    auto maxWidth = 5;

    vector<string> result = {"Hello"};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, AdditionalCaseSingleWordNeedTrailingSpace) {
    Solution solution;

    vector<string> words = {"Hi"};
    auto maxWidth = 4;

    vector<string> result = {"Hi  "};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, AdditionalCaseTwoWordsSingleLineLeft) {
    Solution solution;

    vector<string> words = {"a", "b"};
    auto maxWidth = 5;

    vector<string> result = {"a b  "};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, AdditionalCaseTwoWordsFullJustify) {
    Solution solution;

    vector<string> words = {"a", "b", "cdefg"};
    auto maxWidth = 5;

    vector<string> result = {"a   b", "cdefg"};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, AdditionalCaseOneLineLeftJustify) {
    Solution solution;

    vector<string> words = {"one", "two", "three"};
    auto maxWidth = 20;

    vector<string> result = {"one two three       "};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

TEST(Problem0068, AdditionalCaseExactFitNoPadding) {
    Solution solution;

    vector<string> words = {"ab", "cd"};
    auto maxWidth = 5;

    vector<string> result = {"ab cd"};

    EXPECT_EQ(solution.fullJustify(words, maxWidth), result);
}

#endif
