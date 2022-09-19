#include "EugeneOnegin.h"

char * readFromFileToBuffer (size_t * elements, FILE * readFile)
{
    assert(readFile != NULL);
    assert(elements != NULL);

    *elements = 100;

    char * BUF = (char *)calloc(*elements, sizeof(char));

    int c = 0;
    size_t num = *elements;
    *elements = 0;

    while(1)
    {
        while(*elements < num)
        {
            if((c = getc(readFile)) == EOF)
            {
                BUF[*elements] = '\n';
                break;
            }

            BUF[(*elements)++] = (char)c;
        }

        if(*elements == num)
        {
            (num) *= 2;
            BUF = (char *)realloc(BUF, (num) * sizeof(char));
        }

        else
        {
            BUF = (char *)realloc(BUF, (*elements) * sizeof(char));
            break;
        }
    }

    return BUF;
}

char * createBufferWithFread(size_t * elements, FILE * readFile, size_t * strNum)
{
    assert(readFile != NULL);

    *elements = fileSizeDetection(readFile);

    char * buffer = (char *)calloc(*elements, sizeof(char));

    fread(buffer, sizeof(char), *elements, readFile);

    *strNum = countNumberOfRows(buffer, *elements);

    *elements -= *strNum;

    buffer = (char *)realloc(buffer, (*elements) * sizeof(char));

    return buffer;
}

size_t fileSizeDetection(FILE * read)
{
    assert(read != NULL);

    struct stat stbuf;
    stat("EugeneOnegin.txt", &stbuf);
    off_t fsize = stbuf.st_size;

    /*
    assert(fseek(read, 0, SEEK_END) == 0 &&
           "\nunable to move pointer to end of file\n"); //перемещает указатель на конец файла

    long int fileSize = ftell(read);

    assert(fseek(read, 0, SEEK_SET) == 0 &&
           "\nunable to move pointer to beginning of file\n"); //перемещает указатель нв начало файла
    */

    return fsize / sizeof(char) ;
}

char * takeLineFromBuffer(struct Line * string, char * pBUF)
{
    assert(string != NULL);
    assert(pBUF   != NULL);

    string->strPtr = pBUF;

    int num = 0;

    while(*pBUF != '\n')
    {
        pBUF++;
        num++;
    }

    *pBUF = '\0';
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
            n++;
        }
    }

    n++;

    return n;
}

void createArrayOfStrings(const size_t strNum, char * pBUF, struct Line * EO)
{
    for(size_t i = 0; i < strNum; i++)
    {
        pBUF   = takeLineFromBuffer(&EO[i], pBUF);
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

void outputOriginalText(char * buffer, size_t strNum, FILE * write)
{
    assert(buffer != NULL);

    int len = 0;

    for(size_t i = 0; i < strNum; i++)
    {
        len = printf("%s\n", buffer);
        fprintf(write, "%s\n", buffer);

        buffer += len;
    }

    printf(        "\n----------------------------------------------\n");
    fprintf(write, "\n----------------------------------------------\n");
}

void sortStrings(void * strMassiv, size_t num, size_t elemSize, int (* strCmp)(const void *ptr1, const void *ptr2))
{
    assert(strMassiv != NULL);
    assert(strCmp    != NULL);

    char * strMas = (char*)strMassiv;

    int n = 0, i = 0;

    char * tmp   = 0;
    char * elem1 = 0;
    char * elem2 = 0;

    for(n = num - 1; n >= 1; n--)
    {
        for(i = 0; i < n; i++)
        {
            if (strCmp(strMas + i*elemSize, strMas + (i+1)*elemSize) > 0)
            {
                elem1 = (strMas + i    *elemSize);
                elem2 = (strMas + (i+1)*elemSize);
                swapElements(elem1, elem2, elemSize);
            }
        }
    }
}

void qsortMy(void * strMassiv, int left, int right, size_t elemSize, int (* strCmp)(const void *ptr1, const void *ptr2))
{
    assert(strMassiv != NULL);
    assert(strCmp    != NULL);

    char * strMas = (char*)strMassiv;

    int i = left, j = right;

    char * tmp   = 0;
    char * elem1 = 0;
    char * elem2 = 0;

    char * pivot = strMas + ((left+right)/2)*elemSize;

    while (i <= j)
    {
        while (strCmp(strMas + i*elemSize, pivot) < 0) i++;
        while (strCmp(strMas + j*elemSize, pivot) > 0) j--;

        if (i <= j)
        {
            if (strCmp((strMas + i*elemSize), (strMas + j*elemSize)) > 0)
            {
                elem1 = (strMas + i*elemSize);
                elem2 = (strMas + j*elemSize);
                swapElements(elem1, elem2, elemSize);
            }

            i++;
            j--;
        }

    };

    if (left < j ) qsortMy(strMas, left, j,  elemSize, strCmpFirstLetter);
    if (i < right) qsortMy(strMas, i, right, elemSize, strCmpFirstLetter);
}

char * swapElements(char * elem1, char * elem2, size_t elemSize)
{
    assert(elem1 != NULL);
    assert(elem2 != NULL);

    char tmp = 0;

    char * elem = elem2;

    for(size_t i = 0; i < elemSize; i++)
    {
        tmp = *(elem1 + i);
        *(elem1 + i) = *(elem2 + i);
        *(elem2 + i) = tmp;
    }

    return elem;
}

int strCmpFirstLetter(const void *ptr1, const void *ptr2)
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
        while (*str1 != 0 && isalpha(*str1) == 0)
            str1++;
        while (*str2 != 0 && isalpha(*str2) == 0)
            str2++;

        dif = (*str1 - *str2);

        if (dif != 0 || *str1 == '\0' || *str2 == '\0')
            return dif;

        str1++;
        str2++;
    }

    return dif;
}

int strCmpLastLetter(const void *ptr1, const void *ptr2)
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
        while (*str1 != 0 && isalpha(*str1) == 0)
        {
            str1--;
            len1--;
        }
        while (*str2 != 0 && isalpha(*str2) == 0)
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
