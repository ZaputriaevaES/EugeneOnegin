#ifndef EUGENEONEGIN_H_INCLUDED
#define EUGENEONEGIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct Line{
    char * strPtr;
    int strLen;
    };

struct Text{
    struct Line * strings;
    size_t amountOfElements;
    size_t amountOfStrings;
    };

union number{
    unsigned long long int x;
};

    //отформатировать файл txt убрав все \r

char * readFromFileToBuffer (char * BUF, size_t * elements, FILE * readFile);

size_t fileSizeDetection    (FILE * read);

char * takeLineFromBuffer   (struct Line * string, char * pBUF);

size_t countNumberOfRows    (char * BUF, size_t elements);

void   createArrayOfStrings (const size_t StrNum, char * pBUF, struct Line * EO, struct Line * pEO);

void   stringArrayOutput    (const size_t strNum, struct Line * EO, FILE * write);

void   outputOriginalText   (char * buffer, size_t elements, FILE * write);

void   sortStrings          (void * strMas, size_t num, size_t elemSize, int (* strCmp)(const void *ptr1, const void *ptr2));

//void qsort ( void * first, size_t number, size_t size, int ( * comparator ) ( const void *, const void * ) );

int    strCmpFirstLetter    (const void *ptr1, const void *ptr2);
int    strCmpLastLetter     (const void *ptr1, const void *ptr2);

#endif // EUGENEONEGIN_H_INCLUDED
