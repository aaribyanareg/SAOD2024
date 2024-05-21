#ifndef OPT_HASH_TABLE_H
#define OPT_HASH_TABLE_H

#include <cstddef>

// Структура узла хеш-таблицы
struct Node {
    const char* buffer;
    Node* next;
};

class OptHashTable {
private:
    Node** table;
    size_t tableSize;

    // Хеш-функция
    size_t HashFunction(const char* str);

public:
    OptHashTable(size_t size);
    ~OptHashTable();

    // Инициализация таблицы
    void InitTable();

    // Метод для нахождения наилучшего соответствия
    bool FindTheBest(const char* lookAheadBuffer, int& matchLength, int& matchOffset);

    // Метод для обновления таблицы при сдвиге буфера
    void UpdateTable(const char* oldBuffer, const char* newBuffer);

    // Метод для добавления данных в таблицу
    void FeedTable(const char* newBuffer, size_t length);
};

#endif // OPT_HASH_TABLE_H
