#include "EugeneOnegin.h"

char * readFromFileToBuffer (char * BUF, size_t * elements, FILE * readFile)
{
    assert(BUF != NULL && "\nfailed to allocate buffer memory\n");
    assert(readFile != NULL);
    assert(elements != NULL);

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

size_t fileSizeDetection(FILE * read)
{
    assert(read != NULL);

    assert(fseek(read, 0, SEEK_END) == 0 &&
           "\nunable to move pointer to end of file\n"); //перемещает указатель на конец файла

    long int fileSize = ftell(read);

    assert(fseek(read, 0, SEEK_SET) == 0 &&
           "\nunable to move pointer to beginning of file\n"); //перемещает указатель нв начало файла

    return fileSize / sizeof(char) ;
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

void createArrayOfStrings(const size_t strNum, char * pBUF, struct Line * EO, struct Line * pEO)
{
    for(size_t i = 0; i < strNum; i++)
    {

        pBUF   = takeLineFromBuffer(&EO[i], pBUF);
        //*(pBUF - 1) = '\0';
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

void outputOriginalText(char * buffer, size_t elements, FILE * write)
{
    assert(buffer != NULL);

    for(size_t i = 0; i < elements; i++)
    {
        if(buffer[i] == '\0')
        {
            putchar('\n');
            putc('\n', write);
        }
        else
        {
            putchar(buffer[i]);
            putc(buffer[i], write);
        }
    }

    printf(        "\n----------------------------------------------\n");
    fprintf(write, "\n----------------------------------------------\n");
}

void sortStrings(void * strMas, size_t num, size_t elemSize, int (* strCmp)(const void *ptr1, const void *ptr2))
{
    assert(strMas != NULL);
    assert(strCmp != NULL);

    struct Line * strings = (struct Line *) strMas;
    //void * strings = strMas;

    struct Line temp;
    //void * temp;

    //number tempp = {strings[1]};

    int n = 0, i = 0;

    for(n = num - 1; n >= 1; n--)
    {
        for(i = 0; i < n; i++)
        {
            if (strCmp(strings + i, strings + i + 1) > 0)//strings + i*elemSize, strings + (i+1)*elemSize //strings + i, strings + i + 1
            {
                temp         = strings[i];
                strings[i]   = strings[i+1];
                strings[i+1] = temp;
            }
        }
    }
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
