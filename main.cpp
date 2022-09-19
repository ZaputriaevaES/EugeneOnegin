#include "EugeneOnegin.h"

int main(int argc, char * argv[])
{

//--------------------------------Открытие файлов----------------------------------------------------------------------

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

    struct Text EugeneOnegin = {NULL, 0, 0};

//--------------------------------Создание буфера с помощью realoc-----------------------------------------------------

    //char * buffer = readFromFileToBuffer(&EugeneOnegin.amountOfElements, readFile);

//--------------------------------Создание буфера с помощью fread------------------------------------------------------

    char * buffer = createBufferWithFread(&EugeneOnegin.amountOfElements, readFile, &EugeneOnegin.amountOfStrings);

//---------------------------------------------------------------------------------------------------------------------

    fclose(readFile);

//--------------------------------Создание массива строк---------------------------------------------------------------

    //EugeneOnegin.amountOfStrings = countNumberOfRows(buffer, EugeneOnegin.amountOfElements);

    EugeneOnegin.strings  =  (struct Line *)calloc(EugeneOnegin.amountOfStrings, sizeof(Line));

    createArrayOfStrings (EugeneOnegin.amountOfStrings, buffer, EugeneOnegin.strings);

//--------------------------------Сортировка и вывод массива строк-----------------------------------------------------

    sortStrings              (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpFirstLetter);
    stringArrayOutput        (EugeneOnegin.amountOfStrings, EugeneOnegin.strings, writeFile);

    outputOriginalText       (buffer, EugeneOnegin.amountOfStrings, writeFile);

    sortStrings              (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpLastLetter);
    stringArrayOutput        (EugeneOnegin.amountOfStrings, EugeneOnegin.strings, writeFile);

    qsortMy                  (EugeneOnegin.strings, 0, EugeneOnegin.amountOfStrings - 1, sizeof(Line), strCmpFirstLetter);
    stringArrayOutput        (EugeneOnegin.amountOfStrings, EugeneOnegin.strings, writeFile);

    qsort                    (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpFirstLetter);
    stringArrayOutput        (EugeneOnegin.amountOfStrings, EugeneOnegin.strings, writeFile);

    qsort                    (EugeneOnegin.strings, EugeneOnegin.amountOfStrings, sizeof(Line), strCmpLastLetter);
    stringArrayOutput        (EugeneOnegin.amountOfStrings,EugeneOnegin.strings, writeFile);

//--------------------------------Закрытие файлов и очистка памяти-----------------------------------------------------

    fclose(writeFile);

    free(buffer);
    free(EugeneOnegin.strings);

    return 0;
}
