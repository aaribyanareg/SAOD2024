#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>
#include <memory>

class TrieNode {
public:
    char value;
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    bool isEndOfWord;
    int count;

    TrieNode(char val) : value(val), isEndOfWord(false), count(0) {}
};

class Trie {
public:
    Trie() {
        root = std::make_shared<TrieNode>('\0');
    }

    void insert(const std::string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = std::make_shared<TrieNode>(ch);
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
        current->count++;
    }

    int find(const std::string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return 0;
            }
            current = current->children[ch];
        }
        return current->isEndOfWord ? current->count : 0;
    }

    int size() {
        return sizeHelper(root);
    }

private:
    std::shared_ptr<TrieNode> root;

    int sizeHelper(const std::shared_ptr<TrieNode>& node) {
        int size = 0;
        if (node->isEndOfWord) {
            size++;
        }
        for (const auto& child : node->children) {
            size += sizeHelper(child.second);
        }
        return size;
    }
};

void triedict(const std::string& text, const std::string& word) {
    Trie trie;
    std::string str = "";
    for (const auto& ch : text) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'') {
            str += ch;
        }
        else if (!str.empty()) {
            trie.insert(str);
            str = "";
        }
    }
    if (!str.empty()) {
        trie.insert(str);
    }
    std::cout << "\ndict size: " << trie.size() << std::endl;
    std::cout << word << ": " << trie.find(word) << std::endl;
}

int main() {
    std::ifstream fin("/mnt/data/engwiki_ascii.txt", std::ios::binary);
    if (!fin.is_open()) {
        std::cout << "File not open!" << std::endl;
        return 0;
    }
    std::string text((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

    std::string word = "wiki"; // word to find

    auto time_one = std::chrono::high_resolution_clock::now();
    triedict(text, word);
    auto time_two = std::chrono::high_resolution_clock::now();
    std::cout << "triedict\t" << std::chrono::duration<double>(time_two - time_one).count() << "s" << std::endl;

    return 0;
}
