#include <iostream>
#include <limits>
#include <clocale>
#include "functions.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    int vibor;

    cout << "ЛАБОРАТОРНАЯ РАБОТА №2\n\n";

    cout << "1. Ввод строки через malloc и free\n";
    cout << "2. Ввод строки через calloc, realloc и free\n";
    cout << "3. Работа с файлами\n\n";

    cout << "Выберите задание: ";
    cin >> vibor;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (vibor) {
    case 1:
        if (!Zadanie1()) {
            cout << "Ошибка выделения памяти.\n";
        }
        break;

    case 2:
        if (!Zadanie2()) {
            cout << "Ошибка выделения памяти.\n";
        }
        break;

    case 3:
        if (!Zadanie3("input.txt", "output.txt")) {
            cout << "Ошибка при работе с памятью или файлами.\n";
        }
        break;

    default:
        cout << "Неверный номер задания.\n";
        break;
    }

    return 0;
}