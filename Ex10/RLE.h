#pragma once

unsigned RLEDeflate(const unsigned char* src, unsigned len, unsigned char* dst);
unsigned RLEInflate(const unsigned char* src, unsigned len, unsigned char* dst);
