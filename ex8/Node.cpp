#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>

class Node {
public:
    std::map<char, std::shared_ptr<Node>> children;
    int sufIdx = -1;  // индекс суффикса
    int minIdx = -1;  // минимальный индекс суффиксов поддерева
    int maxIdx = -1;  // максимальный индекс суффиксов поддерева
    int maxLen = 0;   // максимальная длина меток к узлу, которые не пересекаются
    int edgeLength = 0; // длина ребра от родительского узла к текущему узлу
    std::string edgeLabel; // метка ребра от родительского узла к текущему узлу

    void showNode(int depth = 0) {
        for (const auto& child : children) {
            std::cout << std::string(depth, ' ') << child.first << " -> " 
                      << "sufIdx: " << child.second->sufIdx 
                      << ", minIdx: " << child.second->minIdx
                      << ", maxIdx: " << child.second->maxIdx
                      << ", maxLen: " << child.second->maxLen << std::endl;
            child.second->showNode(depth + 1);
        }
    }
};

class SufTree {
private:
    std::shared_ptr<Node> root;
    std::string text;

    void fillLeaves(std::shared_ptr<Node> node, int depth) {
        if (node->children.empty()) {
            node->sufIdx = text.length() - depth;
        } else {
            for (auto& child : node->children) {
                fillLeaves(child.second, depth + 1);
            }
        }
    }

    void fillMin(std::shared_ptr<Node> node) {
        if (node->children.empty()) {
            node->minIdx = node->sufIdx;
        } else {
            node->minIdx = text.length();
            for (auto& child : node->children) {
                fillMin(child.second);
                node->minIdx = std::min(node->minIdx, child.second->minIdx);
            }
        }
    }

    void fillMax(std::shared_ptr<Node> node) {
        if (node->children.empty()) {
            node->maxIdx = node->sufIdx;
        } else {
            node->maxIdx = -1;
            for (auto& child : node->children) {
                fillMax(child.second);
                node->maxIdx = std::max(node->maxIdx, child.second->maxIdx);
            }
        }
    }

    void fillMaxLen(std::shared_ptr<Node> node, int pathLength) {
        for (auto& child : node->children) {
            int childEdgeLength = child.second->edgeLength;
            int newLength = pathLength + childEdgeLength;
            child.second->maxLen = std::min(newLength, child.second->maxIdx - child.second->minIdx);
            fillMaxLen(child.second, newLength);
        }
    }

    std::shared_ptr<Node> findMaxLenNode(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> maxNode = node;
        for (auto& child : node->children) {
            auto candidate = findMaxLenNode(child.second);
            if (candidate->maxLen > maxNode->maxLen) {
                maxNode = candidate;
            }
        }
        return maxNode;
    }

public:
    SufTree(const std::string& str) : text(str) {
        root = std::make_shared<Node>();
        // Построение дерева суффиксов пропущено для краткости
    }

    void fillLeaves() {
        fillLeaves(root, 0);
    }

    void fillMin() {
        fillMin(root);
    }

    void fillMax() {
        fillMax(root);
    }

    void fillMaxLen() {
        fillMaxLen(root, 0);
    }

    void showTree() {
        root->showNode();
    }

    std::string getMaxPattern() {
        auto maxNode = findMaxLenNode(root);
        if (maxNode->maxLen == 0) {
            return "";
        }
        return text.substr(maxNode->minIdx, maxNode->maxLen);
    }
};

int main() {
    std::string text = "banana";
    SufTree tree(text);
    tree.fillLeaves();
    tree.fillMin();
    tree.fillMax();
    tree.fillMaxLen();
    tree.showTree();

    std::string maxPattern = tree.getMaxPattern();
    std::cout << "Max pattern: " << maxPattern << std::endl;

    return 0;
}
