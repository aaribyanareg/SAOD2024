#pragma once
#ifdef PF_EXPORT
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)
#endif

class EXPORT PF {
    char* t = nullptr;  // буфер для образца
    int size = 0;       // размер буферов
public:
    int* p = nullptr;   // буфер префикс-функции
    PF() {}
    PF(const PF&) = delete; // Запретили копирование

    ~PF();

    /// <summary>
    /// Вычисляет префикс-функцию на образце s
    /// </summary>
    /// <param name="s">адрес образца</param>
    /// <param name="sz">размер образца</param>
    void Init(const char s[], int sz);

    /// <summary>
    /// Возвращает значение байта i образца
    /// </summary>
    /// <param name="i">номер символа образца</param>
    /// <returns>запрешеный символ образца или исеключение</returns>
    char pattern(int i) { return t[i]; }

    /// <summary>
    /// возвращает значение i-того элемента префикс-функции на образце.
    /// </summary>
    int operator [] (int i) { return p[i]; }
    operator int() { return size; }
    
    PF& operator = (const PF&) = delete;    // Запретили присваивание
};


