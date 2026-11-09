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
    int i = 0;
    int c; // getchar() возвращает int, поэтому используем int

    cout << "\nЗадание 2. Введите строку (для завершения введите \\0):\n";

    while (i < 998)
    {
        c = getchar(); // Считываем один символ

        // Если встретили конец ввода, завершаем цикл
        if (c == EOF)
        {
            break;
        }

        // Проверяем, является ли символ обратным слешем
        if (c == '\\')
        {
            int next = getchar(); // Считываем следующий символ

            // Если следующий символ — цифра 0, завершаем ввод
            if (next == '0')
            {
                break;
            }

            // Иначе сохраняем оба символа
            stroka2[i++] = static_cast<char>(c);

            if (next == EOF)
            {
                break;
            }

            stroka2[i++] = static_cast<char>(next);
        }

        else
        {
            // Сохраняем обычный символ
            stroka2[i++] = static_cast<char>(c);
        }
    }

    // Завершаем C-строку нулевым символом
    stroka2[i] = '\0';

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