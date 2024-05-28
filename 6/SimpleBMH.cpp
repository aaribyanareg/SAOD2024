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
    const int N = 50;
    const int M = 3;
    const int alphaBetSize = 'b' - 'a' + 1;
    char T[N + 1]{ 0 };
    char t[M + 1]{ 0 };

    srand(time(0));

    for (int i = 0; i < N; i++)
        T[i] = rand() % alphaBetSize + 'a';

    for (int i = 0; i < M; i++)
        t[i] = rand() % alphaBetSize + 'a';

    cout << "T: " << T << endl;
    cout << "t: " << t << endl;

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

    return 0;
}
