#include "stdafx.h"
#include "COBS.h"
#include "RLE.h"
#include <sys/stat.h>

int main()
{
    char cOperation;
    cout << "Enter the first letter of the operation (c - compression; d - decompression):";
    cin >> cOperation; cin.get();

    if (cOperation != 'c' && cOperation != 'd') {
        cout << "Error: can't recognize this operation!...\n";
        return -1;
    }

    string sFInName, sFOutName;

    cout << "Enter name of Input File:" << endl;
    getline(cin, sFInName);
    cout << "Enter name of Output File:" << endl;
    getline(cin, sFOutName);

    struct stat stat_buf;
    int rc = stat(sFInName.c_str(), &stat_buf);
    if (rc == -1) {
        cout << "can't open '" << sFInName << "'" << endl;
        return -1;
    }
    unsigned int inLen = stat_buf.st_size;

    unsigned char* buf = new unsigned char[inLen];

    ifstream ifs;
    ifs.open(sFInName, ios_base::binary);
    if (ifs.is_open())
    {
        ifs.read((char*)buf, inLen);
        ifs.close();
    }
    else {
        cout << "Failed to open input file." << endl;
        delete[] buf;
        return -1;
    }

    unsigned char* cobsBuf = new unsigned char[inLen + inLen / 255 + 1];
    int cobsLen = COBSEncode(buf, inLen, cobsBuf);

    unsigned char* outBuf;
    int outLen;

    if (cOperation == 'c') {
        outBuf = new unsigned char[2 * cobsLen];
        outLen = RLEDeflate(cobsBuf, cobsLen, outBuf);
    }
    else {
        unsigned char* rleDecoded = new unsigned char[inLen];
        int rleLen = RLEInflate(cobsBuf, cobsLen, rleDecoded);

        outBuf = new unsigned char[inLen];
        outLen = COBSDecode(rleDecoded, rleLen, outBuf);
        delete[] rleDecoded;
    }

    ofstream ofs(sFOutName, ios::binary);
    if (ofs.is_open()) {
        ofs.write((char*)outBuf, outLen);
        ofs.close();
    }
    else {
        cout << "Failed to open output file." << endl;
    }

    delete[] buf;
    delete[] cobsBuf;
    delete[] outBuf;

    return 0;
}
