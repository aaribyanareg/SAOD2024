#include "OptHashTable.h"

// Пример функции CompressFile
void CompressFile() {
    OptHashTable hashTable(1000); // Пример размера таблицы, можно настроить

    // Инициализация и подготовка буфера
    // ...

    while (/* условие продолжения цикла */) {
        int matchLength = 0;
        int matchOffset = 0;

        // Использование метода поиска
        hashTable.FindTheBest(lookAheadBuffer, matchLength, matchOffset);

        // Кодирование данных
        // ...

        // Обновление таблицы после сдвига буфера
        hashTable.UpdateTable(oldBuffer, newBuffer);

        // Добавление новых данных в таблицу
        hashTable.FeedTable(newBuffer + bufferShiftPosition, numberOfNewBytes);
    }
}
