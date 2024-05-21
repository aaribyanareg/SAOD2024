#include "OptHashTable.h"
#include <cstring>

// Конструктор
OptHashTable::OptHashTable(size_t size) : tableSize(size) {
    table = new Node * [tableSize];
    for (size_t i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

// Деструктор
OptHashTable::~OptHashTable() {
    for (size_t i = 0; i < tableSize; ++i) {
        Node* node = table[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
    delete[] table;
}

// Хеш-функция
size_t OptHashTable::HashFunction(const char* str) {
    size_t hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % tableSize;
}

// Инициализация таблицы
void OptHashTable::InitTable() {
    for (size_t i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

// Метод для нахождения наилучшего соответствия
bool OptHashTable::FindTheBest(const char* lookAheadBuffer, int& matchLength, int& matchOffset) {
    size_t hashValue = HashFunction(lookAheadBuffer);
    Node* node = table[hashValue];

    int bestLength = 0;
    int bestOffset = 0;

    while (node) {
        int currentLength = 0;
        while (currentLength < MAX_MATCH_LENGTH && lookAheadBuffer[currentLength] == node->buffer[currentLength]) {
            currentLength++;
        }

        if (currentLength > bestLength) {
            bestLength = currentLength;
            bestOffset = lookAheadBuffer - node->buffer;
        }

        node = node->next;
    }

    matchLength = bestLength;
    matchOffset = bestOffset;

    return bestLength > 0;
}

// Метод для обновления таблицы при сдвиге буфера
void OptHashTable::UpdateTable(const char* oldBuffer, const char* newBuffer) {
    for (size_t i = 0; i < tableSize; ++i) {
        Node* node = table[i];
        Node* prev = nullptr;

        while (node) {
            if (node->buffer < oldBuffer) {
                Node* temp = node;
                if (prev) {
                    prev->next = node->next;
                }
                else {
                    table[i] = node->next;
                }
                node = node->next;
                delete temp;
            }
            else {
                node->buffer = newBuffer + (node->buffer - oldBuffer);
                prev = node;
                node = node->next;
            }
        }
    }
}

// Метод для добавления данных в таблицу
void OptHashTable::FeedTable(const char* newBuffer, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        size_t hashValue = HashFunction(newBuffer + i);
        Node* newNode = new Node{ newBuffer + i, table[hashValue] };
        table[hashValue] = newNode;
    }
}
