#include <iostream>
#include <cstring>
#include "functions.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // Задание 1. Символьный массив
    char stroka1[1000];

    cout << "Задание 1. Введите строку:\n";
    cin.getline(stroka1, 1000);

    int dlina = static_cast<int>(strlen(stroka1));

    if (Zadanie1(stroka1))
    {
        cout << "Результат: " << stroka1 << '\n';
    }
    else
    {
    cout << "Найдено меньше двух групп. Строка не изменена.\n";
    }

    // Задание 2. C-строка
    char stroka2[1000];

    cout << "\nЗадание 2. Введите строку:\n";
    cin.getline(stroka2, 1000);

    if (Zadanie2(stroka2))
    {
        cout << "Результат: " << stroka2 << '\n';
    }
    else
    {
        cout << "Найдено меньше двух групп. Строка не изменена.\n";
    }

    // Задание 3. Обработка строки в файле
    char imya_fayla[256];

    cout << "\nЗадание 3.\n";
  

    if (Zadanie3("input.txt", "output.txt"))
    {
        cout << "Результат обработки файла input.txt записан в output.txt.\n";
    }
    else
    {
        cout << "Ошибка обработки файлов или найдено меньше двух групп.\n";
    }

    return 0;
}