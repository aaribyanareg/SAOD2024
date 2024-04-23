#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers;
    cout << "Initial size: " << numbers.size() << ", capacity: " << numbers.capacity() << endl;
    int previous_capacity = numbers.capacity();
    for (int i = 0; i < 32; i++) {
        numbers.push_back(1);
        if (numbers.capacity() != previous_capacity) {
            cout << "After push_back " << i + 1 << ": size = " << numbers.size() << ", capacity = " << numbers.capacity() << endl;
            previous_capacity = numbers.capacity();
        }
    }
    return 0;
}
