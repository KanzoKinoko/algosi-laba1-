#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "functions.h"

using namespace std;



bool Obrabotka_stroki_bez_strlen(char stroka[], int dlina){
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
char* Vvod_malloc() {

    int dlina = 0; 
    char* stroka = (char*)malloc(2);

    if (stroka == nullptr) {

        return nullptr;
    }

    stroka[0] = '\0';

    int simvol;

    while ((simvol = getchar()) != '\n' && simvol != EOF) {

        char* novaya_stroka = (char*)malloc(dlina + 2);

        if (novaya_stroka == nullptr) {
            free(stroka);
            return nullptr;
        }


        for (int i = 0; i < dlina; i++) {
            novaya_stroka[i] = stroka[i];
        }

        novaya_stroka[dlina] = simvol;
        novaya_stroka[dlina + 1] = '\0';
        free(stroka);
        stroka = novaya_stroka;
        dlina++;
    }

    return stroka;
}
char* Vvod_calloc_realloc() {

    int dlina = 0;
    char* stroka = (char*)calloc(1, sizeof(char));

    if (stroka == nullptr) {
        return nullptr;
    }

    int simvol;

    while ((simvol = getchar()) != '\n' && simvol != EOF) {

        char* novaya_stroka = (char*)realloc(stroka, (dlina + 2) * sizeof(char));
        if (novaya_stroka == nullptr) {
            free(stroka);
            return nullptr;
        }

        stroka = novaya_stroka;
        stroka[dlina] = simvol;
        dlina++;
        stroka[dlina] = '\0';
    }

    return stroka;
}
char* Chtenie_fayla_calloc_realloc(FILE* fayl) {

    int dlina = 0;
    char* stroka = (char*)calloc(1, sizeof(char));

    if (stroka == nullptr) {
        return nullptr;
    }

    int simvol;

    while ((simvol = fgetc(fayl)) != '\n' && simvol != EOF) {

        char* novaya_stroka = (char*)realloc(stroka, (dlina + 2) * sizeof(char));
        if (novaya_stroka == nullptr) {
            free(stroka);
            return nullptr;
        }

        stroka = novaya_stroka;
        stroka[dlina] = simvol;
        dlina++;
        stroka[dlina] = '\0';
    }

    return stroka;
}

//задания с лр
bool Zadanie1() {


    cout << "\nВведите строку:\n";
    char* stroka = Vvod_malloc();

    if (stroka == nullptr) {

        return false;
    }

    int dlina = (strlen(stroka));
    bool rezultat = Obrabotka_stroki_bez_strlen(stroka, dlina);

    cout << "\nРезультат:\n";
    cout << stroka << '\n';
    if (!rezultat) {

        // Если групп меньше двух, сообщаем об этом пользователю.
        cout << "Количество групп меньше двух. Строка не изменена.\n";
    }

    free(stroka);
    return true;
}
bool Zadanie2() {
    cout << "\nВведите строку:\n";
    char* stroka = Vvod_calloc_realloc();

    if (stroka == nullptr) {

        return false;
    }

    int dlina =(strlen(stroka));
    bool rezultat = Obrabotka_stroki_bez_strlen(stroka, dlina);

    cout << "\nРезультат:\n";
    cout << stroka << '\n';
    if (!rezultat) {

        cout << "Количество групп меньше двух. Строка не изменена.\n";
    }


    free(stroka);
    return true;
}

bool Zadanie3(const char* imya_fayla1, const char* imya_fayla2) {
    //запись строки в файл
    cout << "\nВведите строку:\n";
    char* stroka = Vvod_calloc_realloc();

    if (stroka == nullptr) {

        return false;
    }

    FILE* vhod = fopen(imya_fayla1, "w");

    if (vhod == nullptr) {
        free(stroka);
        return false;
    }


    fputs(stroka, vhod);
    fclose(vhod);
    free(stroka);


    //чтение строки из файла


    vhod = fopen(imya_fayla1, "r");


    if (vhod == nullptr) {


        return false;
    }


    stroka = Chtenie_fayla_calloc_realloc(vhod);
    fclose(vhod);


    if (stroka == nullptr) {

        return false;
    }

    // обработочка нашей многостродальной строки


    int dlina = static_cast<int>(strlen(stroka));
    bool rezultat = Obrabotka_stroki_bez_strlen(stroka, dlina);


    //запись в файл

    FILE* vyhod = fopen(imya_fayla2, "w");

    if (vyhod == nullptr) {


        free(stroka);


        return false;
    }

    fputs(stroka, vyhod);
    fclose(vyhod);


    cout << "\nРезультат записан в файл "<< imya_fayla2 << '\n';
    if (!rezultat) {

        cout << "Количество групп меньше двух. Строка не изменена.\n";
    }


    free(stroka);
    return true;
}