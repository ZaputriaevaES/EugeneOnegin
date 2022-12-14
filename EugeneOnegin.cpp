#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Line{
    char * strPtr;
    int strLen;
    };

char * readFromFileToBuffer (char * BUF, size_t num, size_t * elements, FILE * readFile);

size_t fileSizeDetection    (FILE * read);

char * takeLineFromBuffer   (struct Line * string, char * pBUF);

size_t countNumberOfRows    (char * BUF, size_t elements);

void   createArrayOfStrings (const size_t StrNum, char * pBUF,
                            struct Line * EO, struct Line * pEO);
void   stringArrayOutput    (const size_t strNum, struct Line * EO, FILE * write);

void   sortStrings          (struct Line * strings, size_t num,
                            int (* strCmp)(struct Line *, struct Line *));

int    strCmpFirstLetter    (struct Line * string1, struct Line * string2);
int    strCmpLastLetter     (struct Line * string1, struct Line * string2);

int    quickSortFromStart   (const void *ptr1, const void *ptr2);
int    quickSortFromTheEnd  (const void *ptr1, const void *ptr2);

int main(int argc, char * argv[])
{

//--------------------------------Открытие файлов----------------------------------------------------

    FILE * readFile = NULL;

    for(int i = 1; i < argc; i++)
    {
        if((readFile  = fopen(argv[i],  "r" )) != NULL)
        {
            break;
        }
    }

    const char * writeFile = "write.txt";
    FILE * write = fopen(writeFile, "w+");
    //assert(write != NULL && "\nunable to open file write.txt\n");

//--------------------------------Создание буфера----------------------------------------------------

    size_t num = 100;
    char * BUF = (char *)calloc(num, sizeof(char));

    size_t elements = 0;
    BUF = readFromFileToBuffer(BUF, num, &elements, readFile);

    //size_t elements = fileSizeDetection(read);

    //if(fread(BUF, sizeof(char), elements, read) < elements)
        //fprintf(stderr, "\nnot all elements were read from the file to the buffer\n");

    //assert(fread(BUF, sizeof(char), Elements, read) < Elements &&
    //       "\nnot all elements were read from the file to the buffer\n")

    fclose(readFile);

//--------------------------------Создание массива строк---------------------------------------------

    const size_t strNum = countNumberOfRows(BUF, elements) + 1; //количество строк

    struct Line * EO   = (struct Line *)calloc(strNum, sizeof(Line)); //основной массив указателей
    struct Line * pEO  = (struct Line *)calloc(strNum, sizeof(Line)); //запасной массив указателей

    createArrayOfStrings (strNum, BUF, EO, pEO);

//--------------------------------Сортировка и вывод массива строк-----------------------------------

    sortStrings              (EO, strNum, strCmpFirstLetter);
    stringArrayOutput        (strNum, EO, write);

    stringArrayOutput        (strNum, pEO, write);

    sortStrings              (EO, strNum, strCmpLastLetter);
    stringArrayOutput        (strNum, EO, write);

    //qsort                    (EO, strNum, sizeof(Line), quickSortFromStart);
    //stringArrayOutput        (strNum, EO, write);

    //qsort                    (EO, strNum, sizeof(Line), quickSortFromTheEnd);
    //stringArrayOutput        (strNum, EO, write);

//--------------------------------Закрытие файлов и очистка памяти-----------------------------------

    fclose(write);

    free(BUF);
    free(EO);
    free(pEO);

    return 0;
}

char * readFromFileToBuffer (char * BUF, size_t num, size_t * elements, FILE * readFile)
{
    assert(BUF != NULL && "\nfailed to allocate buffer memory\n");
    assert(readFile != NULL);
    assert(elements != NULL);

    int c = 0;

    while(1)
    {
        while(*elements < num)
        {
            if((c = getc(readFile)) == EOF)
            {
                BUF[*elements] = '\0';
                break;
            }

            BUF[(*elements)++] = (char)c;
        }

        if(*elements == num)
        {
            num *= 2;
            BUF = (char *)realloc(BUF, num * sizeof(char));
        }

        else
        {
            BUF = (char *)realloc(BUF, *elements * sizeof(char));
            break;
        }
    }

    return BUF;
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

char * takeLineFromBuffer(struct Line * string, char * pBUF)
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

size_t countNumberOfRows(char * BUF, size_t elements)
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

void createArrayOfStrings(const size_t strNum, char * pBUF, struct Line * EO, struct Line * pEO)
{
    for(size_t i = 0; i < strNum; i++)
    {

        pBUF   = takeLineFromBuffer(&EO[i], pBUF);
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

void sortStrings(struct Line * strings, size_t num, int (* strCmp)(struct Line *, struct Line *))
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

int quickSortFromStart(const void *ptr1, const void *ptr2)
{
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);

    const struct Line * string1 = (struct Line *) ptr1;
    const struct Line * string2 = (struct Line *) ptr2;

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

int quickSortFromTheEnd(const void *ptr1, const void *ptr2)
{
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);

    const struct Line * string1 = (struct Line *) ptr1;
    const struct Line * string2 = (struct Line *) ptr2;

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
