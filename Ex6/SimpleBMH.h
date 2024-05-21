#pragma once
#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class BadCharTbl {
private:
    int badChar[256];

public:
    BadCharTbl() {
        for (int i = 0; i < 256; ++i) {
            badChar[i] = 0;
        }
    }

    void Init(const char* s) {
        int len = strlen(s);
        for (int i = 0; i < 256; ++i) {
            badChar[i] = len;
        }
        for (int i = 0; i < len - 1; ++i) {
            badChar[(unsigned char)s[i]] = len - 1 - i;
        }
    }

    int operator[] (unsigned char c) const {
        return badChar[c];
    }
};

list<int> BMH(const char* t, const char* T) {
    list<int> result;
    int tLen = strlen(t);
    int TLen = strlen(T);

    BadCharTbl ctbl;
    ctbl.Init(t);

    int s = 0;
    while (s <= (TLen - tLen)) {
        int j = tLen - 1;

        while (j >= 0 && t[j] == T[s + j])
            j--;

        if (j < 0) {
            result.push_back(s);
            s += (s + tLen < TLen) ? tLen - ctbl[(unsigned char)T[s + tLen]] : 1;
        }
        else
            s += max(1, j - ctbl[(unsigned char)T[s + j]]);
    }

    return result;
}

void generateRandomString(char* s, int N, int alphaBetSize) {
    for (int i = 0; i < N; i++) {
        s[i] = rand() % alphaBetSize + 'a';
    }
    s[N] = '\0';
}
