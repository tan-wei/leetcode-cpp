// Header-only utilities for TreeNode used by generated problems/tests
#pragma once

#include <algorithm>
#include <optional>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace util {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr) {}
};

// Parse a LeetCode-style level-order string like "[3,1,4,null,2]"
inline std::vector<std::optional<int>> parse_level_list(const std::string& s) {
    std::vector<std::optional<int>> out;
    std::string t;
    for (char c : s) {
        if (c == '[' || c == ']') {
            continue;
        }
        t.push_back(c);
    }
    std::istringstream ss(t);
    std::string item;
    while (std::getline(ss, item, ',')) {
        // trim
        size_t a = 0;
        while (a < item.size() && isspace((unsigned char)item[a])) {
            ++a;
        }
        size_t b = item.size();
        while (b > a && isspace((unsigned char)item[b - 1])) {
            --b;
        }
        std::string tok = item.substr(a, b - a);
        if (tok.empty() || tok == "null") {
            out.push_back(std::nullopt);
        } else {
            try {
                int v = std::stoi(tok);
                out.push_back(v);
            } catch (...) {
                out.push_back(std::nullopt);
            }
        }
    }
    return out;
}

// Build a tree from level-order vector of optional<int>
inline TreeNode* to_tree(const std::vector<std::optional<int>>& vals) {
    if (vals.empty() || !vals[0].has_value()) {
        return nullptr;
    }
    TreeNode* root = new TreeNode(vals[0].value());
    std::queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* node = q.front();
        q.pop();
        if (i < vals.size()) {
            if (vals[i].has_value()) {
                node->left = new TreeNode(vals[i].value());
                q.push(node->left);
            }
            ++i;
        }
        if (i < vals.size()) {
            if (vals[i].has_value()) {
                node->right = new TreeNode(vals[i].value());
                q.push(node->right);
            }
            ++i;
        }
    }
    return root;
}

inline TreeNode* to_tree(const std::string& s) {
    return to_tree(parse_level_list(s));
}

// Level-order serialization to vector<optional<int>> (trims trailing nulls)
inline std::vector<std::optional<int>> to_level_list(TreeNode* root) {
    std::vector<std::optional<int>> out;
    if (!root) {
        return out;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        if (n) {
            out.push_back(n->val);
            q.push(n->left);
            q.push(n->right);
        } else {
            out.push_back(std::nullopt);
        }
    }
    // trim trailing nulls
    while (!out.empty() && !out.back().has_value()) {
        out.pop_back();
    }
    return out;
}

inline std::string to_string(TreeNode* root) {
    auto vals = to_level_list(root);
    std::ostringstream ss;
    ss << '[';
    for (size_t i = 0; i < vals.size(); ++i) {
        if (i) {
            ss << ',';
        }
        if (vals[i].has_value()) {
            ss << vals[i].value();
        } else {
            ss << "null";
        }
    }
    ss << ']';
    return ss.str();
}

inline void free_tree(TreeNode* root) {
    if (!root) {
        return;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        if (n->left) {
            q.push(n->left);
        }
        if (n->right) {
            q.push(n->right);
        }
        delete n;
    }
}

} // namespace util
