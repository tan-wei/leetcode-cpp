#ifndef LEETCODE_UTIL_LINKED_LIST_H
#define LEETCODE_UTIL_LINKED_LIST_H

#include <algorithm>
#include <cctype>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace util {

struct ListNode {
    int val;
    ListNode* next;

    ListNode()
        : val(0)
        , next(nullptr) {}

    ListNode(int x)
        : val(x)
        , next(nullptr) {}

    ListNode(int x, ListNode* n)
        : val(x)
        , next(n) {}
};

inline ListNode* to_linked_list(const std::vector<int>& v) {
    ListNode* head = nullptr;
    ListNode** pp = &head;
    for (int x : v) {
        *pp = new ListNode(x);
        pp = &((*pp)->next);
    }
    return head;
}

inline std::vector<int> to_vec(const ListNode* h) {
    std::vector<int> out;
    while (h) {
        out.push_back(h->val);
        h = h->next;
    }
    return out;
}

inline std::string to_string(const ListNode* h) {
    std::ostringstream oss;
    oss << '[';
    bool first = true;
    while (h) {
        if (!first) {
            oss << ',';
        }
        oss << h->val;
        first = false;
        h = h->next;
    }
    oss << ']';
    return oss.str();
}

inline ListNode* to_linked_list(const std::string& s) {
    // Strip whitespace
    std::string t = s;
    std::erase_if(t, [](unsigned char c) { return std::isspace(c); });

    // Strip surrounding brackets
    if (t.size() >= 2 && t.front() == '[' && t.back() == ']') {
        t = t.substr(1, t.size() - 2);
    }
    if (t.empty()) {
        return nullptr;
    }

    // Parse comma-separated integers
    auto split = std::views::split(t, ',') |
                 std::views::filter([](auto&& r) { return !r.empty(); }) |
                 std::views::transform([](auto&& r) -> int {
                     return std::stoi(std::string(r.begin(), r.end()));
                 });
    return to_linked_list(std::vector<int>(split.begin(), split.end()));
}

inline void free_list(ListNode* h) {
    while (h) {
        ListNode* n = h->next;
        delete h;
        h = n;
    }
}

} // namespace util

#endif // LEETCODE_UTIL_LINKED_LIST_H
