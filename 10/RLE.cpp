#include "RLE.h"
#include "stdafx.h"

unsigned RLEDeflate(const unsigned char* src, unsigned len, unsigned char* dst) {
    if (!src || !dst || len == 0) return 0;

    unsigned int index = 0;
    unsigned int dstIndex = 0;

    for (unsigned int i = 0; i < len; i++) {
        unsigned int runLength = 1;

        while (i + 1 < len && src[i] == src[i + 1] && runLength < 255) {
            runLength++;
            i++;
        }

        dst[dstIndex++] = src[i];
        dst[dstIndex++] = runLength;
    }

    return dstIndex;
}

unsigned RLEInflate(const unsigned char* src, unsigned len, unsigned char* dst) {
    if (!src || !dst || len == 0) return 0;

    unsigned int srcIndex = 0;
    unsigned int dstIndex = 0;

    while (srcIndex < len) {
        unsigned char value = src[srcIndex++];
        unsigned char count = src[srcIndex++];

        for (unsigned char j = 0; j < count; j++) {
            dst[dstIndex++] = value;
        }
    }

    return dstIndex;
}
