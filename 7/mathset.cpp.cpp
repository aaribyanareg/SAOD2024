#include <iostream>
#include <set>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

// Функции для вывода множеств
void printSet(const std::set<int>& s) {
    for (const int& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void printUnorderedSet(const std::unordered_set<int>& us) {
    for (const int& elem : us) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Операции объединения и пересечения для set<int>
std::set<int> operator+(const std::set<int>& lhs, const std::set<int>& rhs) {
    std::set<int> result(lhs);
    result.insert(rhs.begin(), rhs.end());
    return result;
}

std::set<int> operator*(const std::set<int>& lhs, const std::set<int>& rhs) {
    std::set<int> result;
    for (const int& elem : lhs) {
        if (rhs.find(elem) != rhs.end()) {
            result.insert(elem);
        }
    }
    return result;
}

// Операции объединения и пересечения для unordered_set<int>
std::unordered_set<int> operator+(const std::unordered_set<int>& lhs, const std::unordered_set<int>& rhs) {
    std::unordered_set<int> result(lhs);
    result.insert(rhs.begin(), rhs.end());
    return result;
}

std::unordered_set<int> operator*(const std::unordered_set<int>& lhs, const std::unordered_set<int>& rhs) {
    std::unordered_set<int> result;
    for (const int& elem : lhs) {
        if (rhs.find(elem) != rhs.end()) {
            result.insert(elem);
        }
    }
    return result;
}

int main() {
    std::set<int> s;
    std::unordered_set<int> us;
    std::srand(std::time(0));

    for (int i = 0; i < 12; ++i) {
        s.insert(std::rand() % 100);
        us.insert(std::rand() % 100);
    }

    std::cout << "Set: ";
    printSet(s);
    std::cout << "Unordered Set: ";
    printUnorderedSet(us);

    // Создание и заполнение двух множеств set<int>
    std::set<int> a;
    std::set<int> b;

    for (int i = 0; i < 12; ++i) {
        a.insert(std::rand() % 100);
        b.insert(std::rand() % 100);
    }

    std::cout << "Set A: ";
    printSet(a);
    std::cout << "Set B: ";
    printSet(b);

    // Об
