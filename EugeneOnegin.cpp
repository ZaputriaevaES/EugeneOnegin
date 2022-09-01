#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Line{
    char * strPtr;
    int strLen;
    };

void openFiles(char * read);
char * pBufgets(struct Line * string, char * pBUF);

void SortStrings(struct Line * strings, int num, int (* StrCmp)(struct Line *, struct Line *));
int StrCmpFirstLetter(struct Line * string1, struct Line * string2);//сравнение двух строк
int StrCmpLastLetter(struct Line * string1, struct Line * string2);//сравнение двух строк


//int cmp(const void *ptr1, const void *ptr2);


int main()
{

//--------------------------------Открытие файлов----------------------------------------------------

    const char * readFile = "EugeneOnegin.txt";

    FILE * read = fopen(readFile, "r");

    assert(read != NULL && "\nunable to open file EugeneOnegin.txt\n");

    FILE * write = fopen("write.txt", "w+");

    //assert(wite != NULL && "\nunable to open file write.txt\n")

//--------------------------------Определение размера файла------------------------------------------


    assert(fseek(read, 0, SEEK_END) == 0 &&
           "\nunable to move pointer to end of file\n"); //перемещает указатель на конец файла

    long int FileSize = ftell(read);

    assert(fseek(read, 0, SEEK_SET) == 0 &&
           "\nunable to move pointer to beginning of file\n"); //перемещает указатель нв начало файла

    size_t Elements = FileSize / sizeof(char);

//--------------------------------Запись из файла в буфер--------------------------------------------

    //printf("%ld %d %d\n", FileSize, sizeof(char), Elements);
    char * BUF = (char *)calloc(Elements, sizeof(char)); //указатель на массив элементов типа char

    assert(BUF != NULL && "\nfailed to allocate buffer memory\n");

    if(fread(BUF, sizeof(char), Elements, read) < Elements) //извлечение из файла read.txt
        fprintf(stderr, "\nnot all elements were read from the file to the buffer\n");

    //assert(fread(BUF, sizeof(char), Elements, read) < Elements &&
    //       "\nnot all elements were read from the file to the buffer\n")

    //assert(fwrite(BUF, sizeof(char), Elements, write) < Elements &&
    //       "\nnot all elements from the buffer were written to the file\n")
    //запись в файл write.txt

    fclose(read);

//--------------------------------Подсчет количество строк-------------------------------------------

    unsigned int n = 0; //количество символов новой строки
    for (unsigned int i = 0; i < Elements; i++)
    {
        if (BUF[i] == '\n')
        {
            BUF[i] = '\0';
            n++;
        }
    }

//--------------------------------Создание массива строк---------------------------------------------

    const int StrNum = n + 1; //количество строк

    char * pBUF = BUF;
    struct Line * EO = (struct Line *)calloc(StrNum, sizeof(Line)); //основной массив указателей
    struct Line * pEO = (struct Line *)calloc(StrNum, sizeof(Line)); //запасной массив указателей

    for(int i = 0; i < StrNum; i++)
    {

        pBUF = pBufgets(&EO[i], pBUF);
        pEO[i] = EO[i];

    }

//--------------------------------Сортировка строк по первой букве-----------------------------------

    SortStrings(EO, StrNum, StrCmpFirstLetter);

//--------------------------------Вывод массива строк------------------------------------------------

    for (int i = 0; i < StrNum; i++)
    {
        printf("%s\n", (&EO[i])->strPtr);
        fprintf(write, "%s\n", (&EO[i])->strPtr);
    }

    printf("\n----------------------------------------------\n");
    fprintf(write, "\n----------------------------------------------\n");

//--------------------------------Вывод массива строк------------------------------------------------

    for (int i = 0; i < StrNum; i++)
    {
        printf("%s\n", (&pEO[i])->strPtr);
        fprintf(write, "%s\n", (&pEO[i])->strPtr);
    }

    printf("\n----------------------------------------------\n");
    fprintf(write, "\n----------------------------------------------\n");

//--------------------------------Сортировка строк по последней букве-----------------------------------

    SortStrings(EO, StrNum, StrCmpLastLetter);

//--------------------------------Вывод массива строк------------------------------------------------

    for (int i = 0; i < StrNum; i++)
    {
        printf("%s\n", (&EO[i])->strPtr);
        fprintf(write, "%s\n", (&EO[i])->strPtr);
    }

//--------------------------------Очистка памяти-----------------------------------------------------

    fclose(write);

    free(EO);

    return 0;
/*
//--------------------------------Сортировка строк по первой букве-----------------------------------

    qsort(EO, 96, sizeof(char*), cmp);


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
*/
}
void openFiles(char * read)
{

}

char * pBufgets(struct Line * string, char * pBUF)
{
    string->strPtr = pBUF;

    int num = 0;

    while(*pBUF != '\0')
    {
        pBUF++;
        num++;
    }

    //*pBUF = '\0';
    pBUF++;

    string->strLen = num;
    //printf("%d\n",string->strLen);

    return pBUF;
}

void SortStrings(struct Line * strings, int num, int (* StrCmp)(struct Line *, struct Line *)) // массив указателей на строки и их количество
{
    struct Line temp;
    int n = 0, i = 0;

    for(n = num - 1; n >= 1; n--)
    {
        for(i = 0; i < n; i++)
        {
            if (StrCmp(&strings[i], &strings[i+1]) > 0)
            {
                //temp = (&strings[i])->strPtr;
                //(&strings[i])->strPtr = (&strings[i+1])->strPtr;
                //(&strings[i+1])->strPtr = temp;

                temp = strings[i];
                strings[i] = strings[i + 1];
                strings[i + 1] = temp;
            }
        }
    }
}

int StrCmpFirstLetter(struct Line * string1, struct Line * string2)
{
    char * str1 = string1->strPtr;
    char * str2 = string2->strPtr;

    int dif = 0; // difference of ANSI codes

    while(dif == 0)
    {
        while ((*str1 >= 1   && *str1 <= 64)||
               (*str1 >= 91  && *str1 <= 96)||
               (*str1 >= 123 && *str1 <= 127))
            str1++;

        while ((*str2 >= 1   && *str2 <= 64)||
               (*str2 >= 91  && *str2 <= 96)||
               (*str2 >= 123 && *str2 <= 127))
            str2++;

        dif = (*str1 - *str2);

        if (dif != 0 || *str1 == '\0' || *str2 == '\0')
            return dif;

        str1++;
        str2++;
    }

    return dif;
}

int StrCmpLastLetter(struct Line * string1, struct Line * string2)
{
    char * str1 = string1->strPtr;
    char * str2 = string2->strPtr;

    int len1 = string1->strLen;
    int len2 = string2->strLen;

    str1 += len1 - 1;
    str2 += len2 - 1;

    int dif = 0; // difference of ANSI codes

    while(dif == 0)
    {
        while ((*str1 >= 1   && *str1 <= 64)||
               (*str1 >= 91  && *str1 <= 96)||
               (*str1 >= 123 && *str1 <= 127))
        {
            str1--;
            len1--;
        }
        while ((*str2 >= 1   && *str2 <= 64)||
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

