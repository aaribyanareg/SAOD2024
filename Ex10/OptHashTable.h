#ifndef OPT_HASH_TABLE_H
#define OPT_HASH_TABLE_H

#include <cstddef>

// ��������� ���� ���-�������
struct Node {
    const char* buffer;
    Node* next;
};

class OptHashTable {
private:
    Node** table;
    size_t tableSize;

    // ���-�������
    size_t HashFunction(const char* str);

public:
    OptHashTable(size_t size);
    ~OptHashTable();

    // ������������� �������
    void InitTable();

    // ����� ��� ���������� ���������� ������������
    bool FindTheBest(const char* lookAheadBuffer, int& matchLength, int& matchOffset);

    // ����� ��� ���������� ������� ��� ������ ������
    void UpdateTable(const char* oldBuffer, const char* newBuffer);

    // ����� ��� ���������� ������ � �������
    void FeedTable(const char* newBuffer, size_t length);
};

#endif // OPT_HASH_TABLE_H
