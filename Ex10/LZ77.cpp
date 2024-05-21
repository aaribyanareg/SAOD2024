#include "OptHashTable.h"

// ������ ������� CompressFile
void CompressFile() {
    OptHashTable hashTable(1000); // ������ ������� �������, ����� ���������

    // ������������� � ���������� ������
    // ...

    while (/* ������� ����������� ����� */) {
        int matchLength = 0;
        int matchOffset = 0;

        // ������������� ������ ������
        hashTable.FindTheBest(lookAheadBuffer, matchLength, matchOffset);

        // ����������� ������
        // ...

        // ���������� ������� ����� ������ ������
        hashTable.UpdateTable(oldBuffer, newBuffer);

        // ���������� ����� ������ � �������
        hashTable.FeedTable(newBuffer + bufferShiftPosition, numberOfNewBytes);
    }
}
