#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Line{
    char * strPtr;
    int strLen;
    };

size_t fileSizeDetection        (FILE * read);
char * pBufgets                 (struct Line * string, char * pBUF);
size_t countingTheNumberOfRows  (char * BUF, size_t elements);

void   creatingAnArrayOfStrings (const size_t StrNum, char * pBUF,
                                struct Line * EO, struct Line * pEO);

void   stringArrayOutput        (const size_t strNum, struct Line * EO, FILE * write);

void   sortStrings              (struct Line * strings, size_t num,
                                int (* strCmp)(struct Line *, struct Line *));
int    strCmpFirstLetter        (struct Line * string1, struct Line * string2);//сравнение двух строк
int    strCmpLastLetter         (struct Line * string1, struct Line * string2);//сравнение двух строк

//int cmp(const void *ptr1, const void *ptr2);


int main()
{

//--------------------------------Открытие файлов----------------------------------------------------

    const char * readFile  = "EugeneOnegin.txt";
    const char * writeFile = "write.txt";

    FILE * read  = fopen(readFile,  "r" );
    FILE * write = fopen(writeFile, "w+");

    assert(read != NULL && "\nunable to open file EugeneOnegin.txt\n");
    //assert(wite != NULL && "\nunable to open file write.txt\n")

    size_t elements = fileSizeDetection(read);

    char * BUF = (char *)calloc(elements, sizeof(char)); //указатель на массив элементов типа char
    char * pBUF = BUF;

    assert(BUF != NULL && "\nfailed to allocate buffer memory\n");

    if(fread(BUF, sizeof(char), elements, read) < elements) //извлечение из файла read.txt
        fprintf(stderr, "\nnot all elements were read from the file to the buffer\n");

    //assert(fread(BUF, sizeof(char), Elements, read) < Elements &&
    //       "\nnot all elements were read from the file to the buffer\n")

    fclose(read);

    const size_t strNum = countingTheNumberOfRows(BUF, elements) + 1; //количество строк

    struct Line * EO   = (struct Line *)calloc(strNum, sizeof(Line)); //основной массив указателей
    struct Line * pEO  = (struct Line *)calloc(strNum, sizeof(Line)); //запасной массив указателей

    creatingAnArrayOfStrings (strNum, pBUF, EO, pEO);

    sortStrings              (EO, strNum, strCmpFirstLetter);
    stringArrayOutput        (strNum, EO, write);

    stringArrayOutput        (strNum, pEO, write);

    sortStrings              (EO, strNum, strCmpLastLetter);
    stringArrayOutput        (strNum, EO, write);


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


size_t fileSizeDetection(FILE * read)
{
    assert(read != NULL);

    assert(fseek(read, 0, SEEK_END) == 0 &&
           "\nunable to move pointer to end of file\n"); //перемещает указатель на конец файла

    long int fileSize = ftell(read);

    assert(fseek(read, 0, SEEK_SET) == 0 &&
           "\nunable to move pointer to beginning of file\n"); //перемещает указатель нв начало файла

    return fileSize / sizeof(char);
}

char * pBufgets(struct Line * string, char * pBUF)
{
    assert(string != NULL);
    assert(pBUF   != NULL);

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

    return pBUF;
}

size_t countingTheNumberOfRows(char * BUF, size_t elements)
{
    assert(BUF != NULL);

    size_t n = 0; //количество символов новой строки
    for (size_t i = 0; i < elements; i++)
    {
        if (BUF[i] == '\n')
        {
            BUF[i] = '\0';
            n++;
        }
    }

    return n;
}

void creatingAnArrayOfStrings(const size_t strNum, char * pBUF, struct Line * EO, struct Line * pEO)
{
    for(size_t i = 0; i < strNum; i++)
    {

        pBUF   = pBufgets(&EO[i], pBUF);
        pEO[i] = EO[i];

    }
}

void stringArrayOutput(size_t strNum, struct Line * EO, FILE * write)
{
    assert(EO    != NULL);
    assert(write != NULL);

    for (size_t i = 0; i < strNum; i++)
    {
        printf(        "%s\n", (&EO[i])->strPtr);
        fprintf(write, "%s\n", (&EO[i])->strPtr);
    }

    printf(        "\n----------------------------------------------\n");
    fprintf(write, "\n----------------------------------------------\n");
}

void sortStrings(struct Line * strings, size_t num, int (* strCmp)(struct Line *, struct Line *)) // массив указателей на строки и их количество
{
    assert(strings != NULL);
    assert(strCmp  != NULL);

    struct Line temp;
    int n = 0, i = 0;

    for(n = num - 1; n >= 1; n--)
    {
        for(i = 0; i < n; i++)
        {
            if (strCmp(&strings[i], &strings[i+1]) > 0)
            {
                temp         = strings[i];
                strings[i]   = strings[i+1];
                strings[i+1] = temp;
            }
        }
    }
}

int strCmpFirstLetter(struct Line * string1, struct Line * string2)
{
    assert(string1 != NULL);
    assert(string2 != NULL);

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

int strCmpLastLetter(struct Line * string1, struct Line * string2)
{
    assert(string1 != NULL);
    assert(string2 != NULL);

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
