#pragma once
#include <map>
#include <set>
#include <unordered_map>

struct Node {
    std::unordered_map<char, Node*> children;
    Node* suffixLink;
    int start, * end;
    int suffixIndex;

    Node(int start, int* end) : start(start), end(end), suffixLink(nullptr), suffixIndex(-1) {}
};
