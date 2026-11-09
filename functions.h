#pragma once
#include <cstdio>

// Обработка строки
bool Obrabotka_stroki_bez_strlen(char stroka[], int dlina);

// Ввод через malloc
char* Vvod_malloc();

// Ввод через calloc и realloc
char* Vvod_calloc_realloc();

// Чтение строки из файла
char* Chtenie_fayla_calloc_realloc(FILE* fayl);

// Задание 1
bool Zadanie1();

// Задание 2
bool Zadanie2();

// Задание 3
bool Zadanie3(const char* imya_fayla1, const char* imya_fayla2);