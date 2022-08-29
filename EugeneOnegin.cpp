#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * Bufgets(char *str, int num, char * BUF);//взятие строки из буфера

int StrCmpFirstLetter(const char * str1, const char * str2);//сравнение двух строк
void SortStringsByFirstLetter(char ** strigs, int num); //сортировка по первой букве

int StrCmpLastLetter(const char * str1, const char * str2);//сравнение двух строк
void SortStringsByLastLetter(char ** strigs, int num); //сортировка по оследней букве


int main()
{

//--------------------------------Открытие файлов----------------------------------------------------

    FILE * read = fopen("EugeneOnegin.txt", "r");
    FILE * write = fopen("write.txt", "w+");

//--------------------------------Определение размера файла------------------------------------------


    fseek(read, 0, SEEK_END); //перемещает указатель на конец файла
    long int FileSize = ftell(read);
    fseek(read, 0, SEEK_SET); //перемещает указатель нв начало файла

    size_t Elements = FileSize / sizeof(char);

//--------------------------------Запись из файла в буфер--------------------------------------------

    //printf("%ld %d %d\n", FileSize, sizeof(char), Elements);
    char * BUF = (char *)calloc(Elements, sizeof(char)); //указатель на массив элементов типа char

    if(BUF == NULL)
        printf("\nERROR1\n");

    if(fread(BUF, sizeof(char), Elements, read) < Elements) //извлечение из файла read.txt
        printf("\nERROR2\n");

    //if(fwrite(BUF, sizeof(char), Elements, write) < Elements) //запись в файл write.txt
        //printf("\nERROR3\n");

    fclose(read);

//--------------------------------Подсчет количество строк-------------------------------------------

    unsigned int n = 0; //количество символов новой строки
    for (unsigned int i = 0; i < Elements; i++)
    {
        if (BUF[i] == '\n')
            n++;
    }

//--------------------------------Создание массива строк---------------------------------------------

    const int StrNum = n + 1; //количество строк
    const int StrLen = 60; //максимальная длина строки

    char * pBUF = BUF;
    char ** EO = (char **)calloc(StrNum, sizeof(char *));
    char ** pEO = (char **)calloc(StrNum, sizeof(char *));

    for(int i = 0; i < StrNum; i++)
    {
        EO[i] = (char*)calloc(StrLen, sizeof(char));
        pBUF = Bufgets(EO[i], StrLen, pBUF);
        pEO[i] = EO[i];
    }

//--------------------------------Сортировка строк по первой букве-----------------------------------

    SortStringsByFirstLetter(EO, StrNum);

//--------------------------------Вывод массива строк------------------------------------------------

    for (int i = 0; i < StrNum; i++)
    {
        printf("%s\n", EO[i]);
        fprintf(write, "%s\n", EO[i]);
    }
    printf("\n----------------------------------------------\n");
    fprintf(write, "\n----------------------------------------------\n");

//--------------------------------Вывод массива строк------------------------------------------------

    for (int i = 0; i < StrNum; i++)
    {
        printf("%s\n", pEO[i]);
        fprintf(write, "%s\n", pEO[i]);
    }
    printf("\n----------------------------------------------\n");
    fprintf(write, "\n----------------------------------------------\n");

//--------------------------------Сортировка строк по последней букве-----------------------------------

    SortStringsByLastLetter(EO, StrNum);

//--------------------------------Вывод массива строк------------------------------------------------

    for (int i = 0; i < StrNum; i++)
    {
        printf("%s\n", EO[i]);
        fprintf(write, "%s\n", EO[i]);
    }

//--------------------------------Очистка памяти-----------------------------------------------------

    fclose(write);

    for (unsigned int i = 0; i < n; i++)
    free(EO[i]);

    free(EO);

    return 0;
}

char * Bufgets(char *str, int num, char * pBUF)
{
    char * pstr = str;

    while(num-- > 0 && *pBUF != '\n')
    {
        *(pstr++) = *(pBUF++);
    }

    *pstr = '\0';
    pBUF++;

    return pBUF;
}

void SortStringsByFirstLetter(char ** strings, int num) // массив указателей на строки и их количество
{
    char * temp = NULL;
    int n = 0, i = 0;

    for(n = num - 1; n >= 1; n--)
    {
        for(i = 0; i < n; i++)
        {
            if (StrCmpFirstLetter(strings[i], strings[i + 1]) > 0)
            {
                temp = strings[i];
                strings[i] = strings[i + 1] ;
                strings[i + 1] = temp;
            }
        }
    }
}

int StrCmpFirstLetter(const char * str1, const char * str2)
{
    int dif = 0; // difference of ANSI codes

    while(dif == 0)
    {
        while ((*str1 >= 1   && *str1 <= 64)||
               (*str1 >= 91  && *str1 <= 96)||
               (*str1 >= 123 && *str1 <= 127))   //*str1 == ' '
            str1++;

        while ((*str2 >= 1   && *str2 <= 64)||
               (*str2 >= 91  && *str2 <= 96)||
               (*str2 >= 123 && *str2 <= 127))   //*str2 == ' '
            str2++;

        dif = (*str1 - *str2);

        if (dif != 0 || *str1 == '\0' || *str2 == '\0')
            return dif;

        str1++;
        str2++;
    }

    return dif;
}

void SortStringsByLastLetter(char ** strings, int num) // массив указателей на строки и их количество
{
    char * temp = NULL;
    int n = 0, i = 0;

    for(n = num - 1; n >= 1; n--)
    {
        for(i = 0; i < n; i++)
        {
            if (StrCmpLastLetter(strings[i], strings[i + 1]) > 0)
            {
                temp = strings[i];
                strings[i] = strings[i + 1] ;
                strings[i + 1] = temp;
            }
        }
    }
}

int StrCmpLastLetter(const char * str1, const char * str2)
{
    int dif = 0; // difference of ANSI codes

    int StrLen = 60;

    str1 += StrLen - 1;
    str2 += StrLen - 1;

    int len1 = StrLen;
    int len2 = StrLen;

    while(dif == 0)
    {
        while ((*str1 >= 0   && *str1 <= 64)||
               (*str1 >= 91  && *str1 <= 96)||
               (*str1 >= 123 && *str1 <= 127))
        {
            str1--;
            len1--;
        }
        while ((*str2 >= 0   && *str2 <= 64)||
               (*str2 >= 91  && *str2 <= 96)||
               (*str2 >= 123 && *str2 <= 127))
        {
            str2--;
            len2--;
        }

        dif = (*str1 - *str2);

        if (dif != 0 || len1 <= 0 || len2 <= 0)
            return dif;

        str1--;
        str2--;
    }

    return dif;
}

