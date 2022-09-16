#include "EugeneOnegin.h"

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

    const char * nameWriteFile = "write.txt";
    FILE * writeFile = fopen(nameWriteFile, "w+");

//--------------------------------Создание буфера с помощью realoc----------------------------------------------------

    struct Text EugeneOnegin;

    /*
    EugeneOnegin.amountOfElements = 100;

    char * buffer = (char *)calloc(EugeneOnegin.amountOfElements, sizeof(char));

    buffer = readFromFileToBuffer(buffer, &EugeneOnegin.amountOfElements, readFile);
    */

//--------------------------------Создание буфера с помощью fread----------------------------------------------------

    ///*
    EugeneOnegin.amountOfElements = fileSizeDetection(readFile);

    char * buffer = (char *)calloc(EugeneOnegin.amountOfElements, sizeof(char));

    fread(buffer, sizeof(char), EugeneOnegin.amountOfElements, readFile);

    EugeneOnegin.amountOfStrings = countNumberOfRows(buffer, EugeneOnegin.amountOfElements);

    EugeneOnegin.amountOfElements -= EugeneOnegin.amountOfStrings;

    buffer = (char *)realloc(buffer, EugeneOnegin.amountOfElements * sizeof(char));
    //*/

//------------------------------------------------------------------------------------

    fclose(readFile);

//--------------------------------Создание массива строк---------------------------------------------

    EugeneOnegin.amountOfStrings = countNumberOfRows(buffer, EugeneOnegin.amountOfElements);

    EugeneOnegin.strings  =  (struct Line *)calloc(EugeneOnegin.amountOfStrings, sizeof(Line));
    struct Line * pEO     =  (struct Line *)calloc(EugeneOnegin.amountOfStrings, sizeof(Line)); //убрать

    createArrayOfStrings (EugeneOnegin.amountOfStrings, buffer, EugeneOnegin.strings, pEO);

//--------------------------------Сортировка и вывод массива строк-----------------------------------

    sortStrings              (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpFirstLetter);
    stringArrayOutput        (EugeneOnegin.amountOfStrings, EugeneOnegin.strings, writeFile);

    stringArrayOutput        (EugeneOnegin.amountOfStrings, pEO, writeFile);
    outputOriginalText       (buffer, EugeneOnegin.amountOfElements, writeFile);

    sortStrings              (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpLastLetter);
    stringArrayOutput        (EugeneOnegin.amountOfStrings, EugeneOnegin.strings, writeFile);

    //qsort                    (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpFirstLetter);
    //stringArrayOutput        (EugeneOnegin.amountOfStrings, EugeneOnegin.strings, writeFile);

    //qsort                    (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpLastLetter);
    //stringArrayOutput        (EugeneOnegin.amountOfStrings,EugeneOnegin.strings, writeFile);

//--------------------------------Закрытие файлов и очистка памяти-----------------------------------

    fclose(writeFile);

    free(buffer);
    free(EugeneOnegin.strings);
    free(pEO);

    return 0;
}
