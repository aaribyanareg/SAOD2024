﻿// quest2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include "utils.h"

#include <iostream>
using namespace std;

// Задание №4
int main() {
    int a = 3, b = 5;
    cout << "Before swap: a = " << a << ", b = " << b << endl;

    Swap(&a, &b); // Вызываем функцию Swap, передавая адреса переменных a и b

    cout << "After swap: a = " << a << ", b = " << b << endl;
    return 0;
}








/*
// Задание №1
int main()
{   
	int x = 3; // Инициализация значения 3
	int* p = &x; // Объявляем указатель p и присваиваем ему адрес переменной x
	cout << x << ' ' << *p << ' ' << p << endl; // Выводит на экран значение x, значение по адресу, на который указывает p (т.е., x), и адрес x
	p++; cout << p << endl; // Увеличиваем указатель p на 1; Выводим новый адрес, на который указывает p
	cout << p - &x << endl;// Выводим разницу между текущим адресом, на который указывает p, и адресом x
    // Это показывает, на сколько позиций в памяти сместился указатель относительно исходного адреса x
}
 
// Задание №2
typedef unsigned char byte; // Нет встроенного byte

int main()
{
    int x = 3; 
    int* p = &x; // Создаем указатель p, который указывает на адрес x

    p--; 
    byte* pb = (byte*)p; // Вернули указатель на x и преобразовали
    
    for (byte* pt = pb; pt - pb < sizeof(int); pt++) // Проходим по каждому байту переменной x
    {
        cout << (int)*pt << ' '; // Выводим как int
    }
    cout << endl; // Перевод строки для удобства чтения вывода
}
 
// Задание №3
// Шаг d: Изначальная попытка написания Swap (будет ошибочной, объяснение в шаге E)
//void Swap(int a, int b) {
//    int temp = a;
//    a = b;
//    b = temp;
//}
// Шаг e: Функция Swap(int a, int b) не работаетпотому что она работает с копиями этих переменных. 
// Изменения, сделанные в функции, не влияют на исходные переменные в main. 
// Это связано с тем, что параметры передаются по значению, а не по адресу или ссылке.

// Шаг f: Корректная реализация функции Swap с использованием указателей
void Swap(int *pa, int *pb) {
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

// Шаг h: Реализация функции Swap с использованием ссылок
void SwapReferences(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    // Шаг B: Объявляем переменные
    int a = 3, b = 5;
    // Шаг C: Проверка до обмена
    cout << "Before swap: a = " << a << ", b = " << b << endl;

    // Шаг G: Вызов функции с указателями
    Swap(&a, &b);
    // Проверка после обмена
    cout << "После замены указателей: a = " << a << ", b = " << b << endl;

    // Шаг H: Вызов функции с ссылками (для наглядности восстановим исходные значения)
    a = 3; b = 5;
    SwapReferences(a, b);
    cout << "После замены ссылок: a = " << a << ", b = " << b << endl;
    return 0;
}
*/

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"






















