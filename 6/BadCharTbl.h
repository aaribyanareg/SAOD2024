#ifndef BADCHARTBL_H
#define BADCHARTBL_H

#include <cstring>

class BadCharTbl {
private:
    int badChar[256];

public:
    BadCharTbl() {
        std::fill(badChar, badChar + 256, 0);
    }

    void Init(const char* s) {
        int len = strlen(s);
        std::fill(badChar, badChar + 256, len);

        // Filling the bad character table according to the Boyer-Moore-Horspool algorithm
        for (int i = 0; i < len - 1; ++i) {
            badChar[(unsigned char)s[i]] = len - 1 - i;
        }
    }

    int operator[](unsigned char c) const {
        return badChar[c];
    }
};

#endif // BADCHARTBL_H
