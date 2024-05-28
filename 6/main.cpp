#include <iostream>
#include <list>
#include <cstring>
#include <chrono>
#include "BadCharTbl.h"

using namespace std;

list<int> BMH(const char* t, const char* T) {
    list<int> result;
    int t_len = strlen(t);
    int T_len = strlen(T);

    BadCharTbl bct;
    bct.Init(t);

    int shift = 0;
    while (shift <= (T_len - t_len)) {
        int j = t_len - 1;

        while (j >= 0 && t[j] == T[shift + j])
            j--;

        if (j < 0) {
            result.push_back(shift);
            shift += (shift + t_len < T_len) ? t_len - bct[T[shift + t_len]] : 1;
        }
        else {
            shift += max(1, j - bct[T[shift + j]]);
        }
    }

    return result;
}

int main() {
    // Example setup for different lengths N and pattern length M
    const int alphaBetSize = 'b' - 'a' + 1;
    const int M = 6;

    // Varying N in range from 128 to 8192
    for (int N = 128; N <= 8192; N *= 4) {
        char* T = new char[N + 1] {0};
        char t[] = "abcabc"; // Example pattern with length M

        srand(time(0));

        for (int i = 0; i < N; i++)
            T[i] = rand() % alphaBetSize + 'a';

        cout << "N = " << N << endl;

#ifdef _BM_
        auto start = chrono::steady_clock::now();
        list<int> result = BMH(t, T);
        auto stop = chrono::steady_clock::now();
        auto dt = chrono::duration_cast<chrono::microseconds>(stop - start).count();
#else
        string sT(T);
        auto start = chrono::steady_clock::now();
        list<int> result;
        size_t pos = sT.find(t, 0);
        while (pos != string::npos) {
            result.push_back(pos);
            pos = sT.find(t, pos + 1);
        }
        auto stop = chrono::steady_clock::now();
        auto dt = chrono::duration_cast<chrono::microseconds>(stop - start).count();
#endif

        cout << "Found positions: ";
        for (int pos : result)
            cout << pos << " ";
        cout << endl;

        cout << "Time taken: " << dt << " microseconds" << endl;

        delete[] T;
    }

    return 0;
}
