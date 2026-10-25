#include <fstream>
#include <cstring>
#include "functions.h"


static bool Obrabotka_stroki_bez_strlen(char stroka[], int dlina){
    int kolichestvo = 0;
    int poziciya = 0;

    // часть 1: считаем количество групп из пяти букв "е".

    
    while (poziciya + 10 <= dlina)
    {
        bool naydena_gruppa = true;
    
        for (int i = 0; i < 5; i++)
        {
            int poz = poziciya + i * 2;

            if (static_cast<unsigned char>(stroka[poz]) != 0xD0 ||
                static_cast<unsigned char>(stroka[poz + 1]) != 0xB5)
            {
                naydena_gruppa = false;
                break;
            }
        }

        if (naydena_gruppa)
        {
            kolichestvo++;
            poziciya += 10;
        }
        else
        {
            poziciya++;
        }
    }

    // если групп меньше двух то скип
    if (kolichestvo <= 1)
    {
        return false;
    }

    // часть 2: заменяем группы на E
    poziciya = 0;
    int obrabotano = 0;

    while (poziciya + 10 <= dlina)
    {
        bool naydena_gruppa = true;
        // тут мы ищем группу
        for (int i = 0; i < 5; i++)
        {
            int poz = poziciya + i * 2;
            //русская "е"(которая указана в тз,ничё не знаю) в UTF-8 выглядит так: D0 B5
            if (static_cast<unsigned char>(stroka[poz]) != 0xD0 ||
                static_cast<unsigned char>(stroka[poz + 1]) != 0xB5)
            {
                naydena_gruppa = false;
                break;//тут нету группы
            }
        }

        if (naydena_gruppa)
        {
            // Заменяем первую букву группы на латинскую E.
            stroka[poziciya] = 'E';

            obrabotano++;

            if (obrabotano == kolichestvo)
            {
                // последняя группа: сразу вставляем '?' после E,така как E и ? занимают вместе 2 байта.
                stroka[poziciya + 1] = '?';

                // сдвигаем остаток строки на 8 байт
                for (int j = poziciya + 2; j <= dlina - 8; j++)
                {
                    stroka[j] = stroka[j + 8];
                }

                dlina -= 8;
                stroka[dlina] = '\0';//условно затирка
                break;
            }
            else
            {
                // Не последняя группа: оставляем E,
                // свдигаем на 9 байт группы,так как в тз указана "E" англйиская
                for (int j = poziciya + 1; j <= dlina - 9; j++)
                {
                    stroka[j] = stroka[j + 9];
                }

                dlina -= 9;
                stroka[dlina] = '\0';
                poziciya++;
            }
        }
        else//если в первом for не нашли группу переходим на следующию позицию
        {
            poziciya++;
        }
    }

    return true;
}


// Задание 1. Строка как массив символов.
bool Zadanie1(char stroka[]){
    int dlina = 0;

    while (stroka[dlina] != '\0')
    {
        dlina++;
    }

    return Obrabotka_stroki_bez_strlen(stroka, dlina);
}

// Задание 2. Строка как строка в стиле языка Си (строка, завершающаяся символом '\0').
bool Zadanie2(char stroka[]){
    int dlina = static_cast<int>(strlen(stroka));
    return Obrabotka_stroki_bez_strlen(stroka, dlina);
}


// Задание 3. Строка хранится в файле.

bool Zadanie3(const char* imya_fayla1, const char* imya_fayla2)
{
    // Открываем первый файл для чтения.
    FILE* vhod = fopen(imya_fayla1, "r");

    // Проверяем, удалось ли открыть входной файл.
    if (vhod == nullptr)
    {
        return false;
    }

    // Создаём один массив для хранения строки из файла.
    char stroka[1000];

    // проверка удалось ли считать строку,и при этом строка сохраняется в массив,т.к. сначала вызывается fgets(stroka, 1000, vhod)
    if (fgets(stroka, 1000, vhod) == nullptr)
    {
        fclose(vhod);
        return false;
    }

    // Закрываем входной файл.
    fclose(vhod);

    // Вычисляем длину строки с помощью strlen.
    int dlina = static_cast<int>(strlen(stroka));

    // Убираем символ переноса строки, если он был считан.
    if (dlina > 0 && stroka[dlina - 1] == '\n')
    {
        stroka[--dlina] = '\0';
    }

    // Обрабатываем строку непосредственно в этом же массиве.
    bool rezultat = Obrabotka_stroki_bez_strlen(stroka, dlina);

    // Открываем второй файл для записи.
    FILE* vyhod = fopen(imya_fayla2, "w");

    // Проверяем, удалось ли открыть выходной файл.
    if (vyhod == nullptr)
    {
        return false;
    }

    // Записываем обработанную строку в выходной файл.
    fputs(stroka, vyhod);

    // Закрываем выходной файл.
    fclose(vyhod);

    // Возвращаем результат обработки строки.
    return rezultat;
}