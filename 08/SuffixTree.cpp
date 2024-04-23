#include "Node.h"
#include <iostream>
#include <string>
#include <vector>

class SuffixTree {
private:
    std::string text;
    Node* root;
    Node* lastNewNode = nullptr;
    Node* activeNode = nullptr;

    int activeEdge = -1;
    int activeLength = 0;

    int remainingSuffixCount = 0;
    int leafEnd = -1;
    int* rootEnd = nullptr;
    int* splitEnd = nullptr;
    int size = -1;

    Node* newNode(int start, int* end) {
        Node* node = new Node(start, end);
        node->suffixLink = root;
        return node;
    }

    int edgeLength(Node* n) {
        return *n->end - n->start + 1;
    }

    bool walkDown(Node* currNode) {
        if (activeLength >= edgeLength(currNode)) {
            activeEdge += edgeLength(currNode);
            activeLength -= edgeLength(currNode);
            activeNode = currNode;
            return true;
        }
        return false;
    }

    void extendSuffixTree(int pos) {
        leafEnd = pos;
        remainingSuffixCount++;
        lastNewNode = nullptr;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0) activeEdge = pos;

            if (activeNode->children.find(text[activeEdge]) == activeNode->children.end()) {
                activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
            }
            else {
                Node* next = activeNode->children[text[activeEdge]];
                if (walkDown(next)) continue;

                if (text[next->start + activeLength] == text[pos]) {
                    if (lastNewNode != nullptr && activeNode != root) {
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = nullptr;
                    }
                    activeLength++;
                    break;
                }

                splitEnd = new int;
                *splitEnd = next->start + activeLength - 1;

                Node* split = newNode(next->start, splitEnd);
                activeNode->children[text[activeEdge]] = split;

                split->children[text[pos]] = newNode(pos, &leafEnd);
                next->start += activeLength;
                split->children[text[next->start]] = next;

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = split;
                }

                lastNewNode = split;
            }

            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            }
            else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }

    void setSuffixIndexByDFS(Node* n, int labelHeight) {
        if (n == nullptr) return;

        bool leaf = true;
        for (auto& child : n->children) {
            if (child.second) {
                leaf = false;
                setSuffixIndexByDFS(child.second, labelHeight + edgeLength(child.second));
            }
        }
        if (leaf) {
            n->suffixIndex = size - labelHeight;
        }
    }

public:
    SuffixTree(const std::string& text) : text(text) {
        size = text.size();
        rootEnd = new int;
        *rootEnd = -1;

        root = new Node(-1, rootEnd);
        activeNode = root;
    }

    void buildTree() {
        for (int i = 0; i < size; i++) {
            extendSuffixTree(i);
        }
        int labelHeight = 0;
        setSuffixIndexByDFS(root, labelHeight);
    }

    ~SuffixTree() {
        // Destructor to clean up allocated nodes
    }

    void printTree(Node* node, std::string indent = "", int last = 0) {
        if (node == nullptr) {
            return;
        }

        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            if (it != node->children.begin()) {
                indent += last == 2 ? "    " : "|   ";
            }

            std::cout << indent;

            if (it == std::prev(node->children.end())) {
                std::cout << "\\-- ";
                last = 2;
            }
            else {
                std::cout << "|-- ";
                last = 1;
            }

            std::string edgeLabel = text.substr(it->second->start, *it->second->end - it->second->start + 1);
            std::cout << edgeLabel << " (" << it->second->start << "," << *it->second->end << ")" << std::endl;
            printTree(it->second, indent, last);
        }

        if (node->children.empty()) {
            std::cout << indent << " [Leaf]" << std::endl;
        }
    }

    void displayTree() {
        std::cout << "Root" << std::endl;
        printTree(root);
    }

};

int main() {
    std::string text = "abcabxabcd";
    SuffixTree st(text);
    st.buildTree();
    std::cout << "Suffix Tree Built! Displaying the tree:" << std::endl;
    st.displayTree();
    return 0;
}

