#ifndef EUGENEONEGIN_H_INCLUDED
#define EUGENEONEGIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>

struct Line{
    char * strPtr;
    int strLen;
    };

struct Text{
    struct Line * strings;
    size_t amountOfElements;
    size_t amountOfStrings;
    };

char * readFromFileToBuffer  (size_t * elements, FILE * readFile);

char * createBufferWithFread (size_t * elements, FILE * readFile, size_t * strNum);

size_t fileSizeDetection     (FILE * read);

char * takeLineFromBuffer    (struct Line * string, char * pBUF);

size_t countNumberOfRows     (char * BUF, size_t elements);

void   createArrayOfStrings  (const size_t StrNum, char * pBUF, struct Line * EO);

void   stringArrayOutput     (const size_t strNum, struct Line * EO, FILE * write);

void   outputOriginalText    (char * buffer, size_t elements, FILE * write);

void   sortStrings           (void * strMas, size_t num, size_t elemSize, int (* strCmp)(const void *ptr1, const void *ptr2));

void   qsortMy               (void * arrive, int left, int right, size_t elemSize, int (* strCmp)(const void *ptr1, const void *ptr2));

char * swapElements          (char * elem1, char * elem2, size_t elemSize);

int    strCmpFirstLetter    (const void *ptr1, const void *ptr2);
int    strCmpLastLetter     (const void *ptr1, const void *ptr2);

#endif // EUGENEONEGIN_H_INCLUDED
