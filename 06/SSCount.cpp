#include "stdafx.h"
#include "PF.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <cstdlib>
#include <ctime>

unsigned SSCount(const char* s) {
    PF pf;
    std::string str(s);
    std::unordered_set<std::string> uniqueSubstrings;

    for (int start = 0; start < str.length(); ++start) {
        for (int len = 1; start + len <= str.length(); ++len) {
            std::string sub = str.substr(start, len);
            pf.Init(sub.c_str(), sub.length());
            uniqueSubstrings.insert(sub);
        }
    }

    return uniqueSubstrings.size();
}

unsigned SimpleSSCount(const char* s) {
    std::string str(s);
    std::vector<std::string> substrings(10000, "");

    int count = 0;

    for (int len = 1; len <= str.length(); ++len) {
        for (int start = 0; start <= str.length() - len; ++start) {
            std::string sub = str.substr(start, len);
            bool found = false;

            for (int i = 0; i < substrings.size(); ++i) {
                if (substrings[i] == sub) {
                    found = true;
                    break;
                }
                if (substrings[i].length() == 0) {
                    substrings[i] = sub;
                    found = true;
                    count++;
                    break;
                }
            }

            if (!found) {
                break;
            }
        }
    }

    return count;
}

std::string generateRandomString(size_t length) {
    std::string str(length, ' '); // Создаем строку заданной длины
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charsetSize = sizeof(charset) - 1;

    for (size_t i = 0; i < length; i++) {
        int key = rand() % charsetSize;
        str[i] = charset[key];
    }

    return str;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::string testString = generateRandomString(128);

    auto startSSCount = std::chrono::high_resolution_clock::now();
    unsigned resultSSCount = SSCount(testString.c_str());
    auto endSSCount = std::chrono::high_resolution_clock::now();

    auto startSimpleSSCount = std::chrono::high_resolution_clock::now();
    unsigned resultSimpleSSCount = SimpleSSCount(testString.c_str());
    auto endSimpleSSCount = std::chrono::high_resolution_clock::now();

    std::cout << "Random string used: " << testString << std::endl;
    std::cout << "Number of unique substrings using SSCount: " << resultSSCount << std::endl;
    std::cout << "Time taken by SSCount: " << std::chrono::duration_cast<std::chrono::milliseconds>(endSSCount - startSSCount).count() << " ms" << std::endl;
    std::cout << "Number of unique substrings using SimpleSSCount: " << resultSimpleSSCount << std::endl;
    std::cout << "Time taken by SimpleSSCount: " << std::chrono::duration_cast<std::chrono::milliseconds>(endSimpleSSCount - startSimpleSSCount).count() << " ms" << std::endl;

    srand(static_cast<unsigned int>(time(nullptr)));
    testString = generateRandomString(1024);

    auto start = std::chrono::high_resolution_clock::now();
    unsigned result = SSCount(testString.c_str());
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Number of unique substrings for a string of length 1024: " << result << std::endl;
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    return 0;
}
