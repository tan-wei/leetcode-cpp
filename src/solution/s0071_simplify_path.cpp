/**
 * File              : s0071_simplify_path.cpp
 * Project           : leetcode-cpp
 * Author            : Wei Tan <tanwei.winterreise@gmail.com>
 * Date              : 2026-11-09 15:48:42
 * Last Modified Date: 2026-11-09 16:53:12
 * Last Modified By  : Wei Tan <tanwei.winterreise@gmail.com>
 */

/**
 * [0071] Simplify Path
 *
 * You are given an absolute path for a Unix-style file system, which always
 * begins with a slash '/'. Your task is to transform this absolute path into
 * its simplified canonical path. The rules of a Unix-style file system are as
 * follows: A single period '.' represents the current directory. A double
 * period '..' represents the previous/parent directory. Multiple consecutive
 * slashes such as '//' and '///' are treated as a single slash '/'. Any
 * sequence of periods that does not match the rules above should be treated as
 * a valid directory or file name. For example, '...' and '....' are valid
 * directory or file names. The simplified canonical path should follow these
 * rules: The path must start with a single slash '/'. Directories within the
 * path must be separated by exactly one slash '/'. The path must not end with a
 * slash '/', unless it is the root directory. The path must not have any single
 * or double periods ('.' and '..') used to denote current or parent
 * directories. Return the simplified canonical path.
 *
 * Example 1:
 * Input: path = "/home/"
 * Output: "/home"
 * Explanation:
 * The trailing slash should be removed.
 * Example 2:
 * Input: path = "/home//foo/"
 * Output: "/home/foo"
 * Explanation:
 * Multiple consecutive slashes are replaced by a single one.
 * Example 3:
 * Input: path = "/home/user/Documents/../Pictures"
 * Output: "/home/user/Pictures"
 * Explanation:
 * A double period ".." refers to the directory up a level (the parent
 * directory).
 * Example 4:
 * Input: path = "/../"
 * Output: "/"
 * Explanation: Going one level up from the root directory is not possible.
 * Example 5:
 * Input: path = "/.../a/../b/c/../d/./"
 * Output: "/.../b/d"
 * Explanation:
 * "..." is a valid name for a directory in this problem.
 *
 * Constraints:
 * 	1 <= path.length <= 3000
 * 	path consists of English letters, digits, period '.', slash '/' or '_'.
 * 	path is a valid absolute Unix path.
 *
 */

// problem: https://leetcode.com/problems/simplify-path/
// discuss: https://leetcode.com/problems/simplify-path/discuss/

#include <string>
#include <vector>

using namespace std;

// submission codes start here

class Solution {
public:
    // cppcheck-suppress passedByValue
    string simplifyPath(string path) {
        int cur = 0;
        vector<string> dictionaries;
        while (cur < path.length()) {
            auto dictionary_name = getNextDictionaryName(path, cur);
            if (dictionary_name == ".") {
                // ignore
            } else if (dictionary_name == "..") {
                if (!dictionaries.empty()) {
                    dictionaries.pop_back();
                }
            } else if (!dictionary_name.empty()) {
                dictionaries.push_back(dictionary_name);
            }
        }

        if (dictionaries.empty()) {
            return "/";
        }

        string result;
        for (const auto& d : dictionaries) {
            result += "/" + d;
        }

        return result;
    }

private:
    string getNextDictionaryName(const string& path, int& pos) {
        string dictionary_name;
        while (pos < path.length() && path[pos] == '/') {
            pos++;
        }
        while (pos < path.length() && path[pos] != '/') {
            dictionary_name.push_back(path[pos]);
            pos++;
        }

        return dictionary_name;
    }
};

// submission codes end

#if defined(ENABLE_GTEST)
#include <gtest/gtest.h>

TEST(Problem0071, Example1) {
    Solution solution;

    auto path = "/home/"s;

    auto result = "/home"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, Example2) {
    Solution solution;

    auto path = "/home//foo/"s;

    auto result = "/home/foo"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, Example3) {
    Solution solution;

    auto path = "/home/user/Documents/../Pictures"s;

    auto result = "/home/user/Pictures"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, Example4) {
    Solution solution;

    auto path = "/../"s;

    auto result = "/"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, Example5) {
    Solution solution;

    auto path = "/.../a/../b/c/../d/./"s;

    auto result = "/.../b/d"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, AdditionalCaseOnlyRoot) {
    Solution solution;

    auto path = "/"s;

    auto result = "/"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, AdditionalCaseMultiDotDir) {
    Solution solution;

    auto path = "/..../../abc"s;

    auto result = "/abc"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, AdditionalCaseSequentialDot) {
    Solution solution;

    auto path = "/a/b/./././c"s;

    auto result = "/a/b/c"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

TEST(Problem0071, AdditionalCaseContinuousParent) {
    Solution solution;

    auto path = "/a/b/c/../../d"s;

    auto result = "/a/d"s;

    EXPECT_EQ(solution.simplifyPath(path), result);
}

#endif
