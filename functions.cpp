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
    std::ifstream vhod(imya_fayla1);

    if (!vhod.is_open())
    {
        return false;
    }

    char stroka[1000];

    vhod.getline(stroka, 1000);
    vhod.close();

    int dlina = 0;
    while (stroka[dlina] != '\0')
    {
        dlina++;
    }

    bool rezultat = Obrabotka_stroki_bez_strlen(stroka, dlina);

    std::ofstream vyhod(imya_fayla2);

    if (!vyhod.is_open())
    {
        return false;
    }

    vyhod << stroka;
    vyhod.close();

    return rezultat;
}