#include "SimpleBMH.h"

int main() {
    const int N = 50;
    const int M = 3;
    const int alphaBetSize = 2; // Using 'a' and 'b' for simplicity

    char T[N + 1];
    char t[M + 1];

    generateRandomString(T, N, alphaBetSize);
    generateRandomString(t, M, alphaBetSize);

    cout << "T: " << T << endl;
    cout << "t: " << t << endl;

#ifdef _BM_
    list<int> result = BMH(t, T);
    for (int e : result) {
        cout << e << ' ';
    }
    cout << endl;
#else
    string sT(T);
    list<int> result;
    size_t pos = sT.find(t);
    while (pos != string::npos) {
        result.push_back(pos);
        pos = sT.find(t, pos + 1);
    }
    for (int e : result) {
        cout << e << ' ';
    }
    cout << endl;
#endif

    return 0;
}
