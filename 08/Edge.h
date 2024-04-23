#pragma once
#include "Node.h"

struct Edge {
    Node* node = nullptr;
    int start, end;

    Edge(Node* node, int start, int end) : node(node), start(start), end(end) {}
};
