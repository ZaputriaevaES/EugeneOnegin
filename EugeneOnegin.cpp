#include <stdio.h>
#include <stdlib.h>
#include <string.h>//fread

int strcmpmy(const char * str1, const char * str2);
void SortStringsByFirstLetter(char ** strigs, int num); //сортировка по первой букве
void SortStringsByLastLetter(char ** strigs, int num); //сортировка по оследней букве
int cmp(const void *ptr1, const void *ptr2);

int main()
{
    const int n = 96;
    const int m = 60;

//--------------------------------Открытие файлов------------------------------------------------------

    FILE * read = fopen("EugeneOnegin.txt", "r");
    FILE * write = fopen("write.txt", "w+");

//--------------------------------Запись из файла в массив построчно------------------------------------------------------

    char ** EO = (char **)calloc(n, sizeof(char *));//массив указателей на строки
    //char ** pEO = (char **)calloc(n, sizeof(char *));
    //int * num = (int *)calloc(n, sizeof(int));//массив длин строк

    char ch = 0;

    for(int i = 0; i < n; i++)
    {
        EO[i] = (char*)calloc(m, sizeof(char));

        fgets(EO[i], m, read);
    }

    fclose(read);
    fclose(write)

//--------------------------------Сортировка строк по первой букве------------------------------------------------------

    SortStringsByFirstLetter(EO, n);
    //qsort(EO, 96, sizeof(char*), cmp);

//--------------------------------------------------------------------------------------

//--------------------------------Вывод массива строк------------------------------------------------------

    for (int i = 0; i < n; i++)
    {
        printf("%s", EO[i]);
    }

//--------------------------------Очистка памяти------------------------------------------------------

    for (int i = 0; i < n; i++)
        free(EO[i]);

    free(EO);

    return 0;
}

void SortStringsByFirstLetter(char ** strings, int num) // массив указателей на строки и их количество
{
    char * temp = NULL;
    int n = 0, i = 0;

    for(n = num - 1; n >= 1; n--)
    {
        for(i = 0; i < n; i++)
        {
            if (strcmpmy(strings[i], strings[i + 1]) > 0)
            {
                temp = strings[i];
                strings[i] = strings[i + 1] ;
                strings[i + 1] = temp;
            }
        }
    }
}

void SortStringsByLastLetter(char ** strigs, int num)
{

}

int strcmpmy(const char * str1, const char * str2)
{
    int dif = 0; // difference of ANSI codes

    while(dif == 0)
    {
        while (*str1 == ' ')
            str1++;

        while (*str2 == ' ')
            str2++;

        dif = (*str1 - *str2);

        if (dif != 0 && (*str1 == '\0' || *str2 == '\0'))
            return dif;

        str1++;
        str2++;
    }

    return dif;
}

int cmp(const void *ptr1, const void *ptr2)
{
    const char * str1 = (char *) ptr1;
    const char * str2 = (char *) ptr2;

    int dif = 0; // difference of ANSI codes

    while((dif = (*str1 - *str2)) == 0 && *str1 != '\0' && *str2 != '\0')
    {
        str1++;
        str2++;
    }

    return dif;
}

