#include <iostream>
#include <set>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

void printSet(const std::set<int>& s);
void printUnorderedSet(const std::unordered_set<int>& us);
std::set<int> operator+(const std::set<int>& a, const std::set<int>& b);
std::set<int> operator*(const std::set<int>& a, const std::set<int>& b);

int main() {
    std::srand(std::time(0)); // для генерации случайных чисел

    std::set<int> setA, setB;
    std::unordered_set<int> unorderedSetA, unorderedSetB;

    // Заполнение множеств случайными числами
    for (int i = 0; i < 15; ++i) {
        setA.insert(std::rand() % 100);
        setB.insert(std::rand() % 100);
        unorderedSetA.insert(std::rand() % 100);
        unorderedSetB.insert(std::rand() % 100);
    }

    // Вывод множеств
    std::cout << "Set A: ";
    printSet(setA);
    std::cout << "Set B: ";
    printSet(setB);

    std::cout << "Unordered Set A: ";
    printUnorderedSet(unorderedSetA);
    std::cout << "Unordered Set B: ";
    printUnorderedSet(unorderedSetB);

    // Операция объединения
    std::set<int> unionSet = setA + setB;
    std::cout << "Union of Set A and Set B: ";
    printSet(unionSet);

    // Операция пересечения
    std::set<int> intersectionSet = setA * setB;
    std::cout << "Intersection of Set A and Set B: ";
    printSet(intersectionSet);

    return 0;
}

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

std::set<int> operator+(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

std::set<int> operator*(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result;
    for (const int& elem : a) {
        if (b.find(elem) != b.end()) {
            result.insert(elem);
        }
    }
    return result;
}
