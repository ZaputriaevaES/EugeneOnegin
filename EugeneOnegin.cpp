#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    const int n = 100;
    const int m = 60;


    FILE * read = fopen("EugeneOnegin.txt", "r");
    FILE * whrite = fopen("write.txt", "a");

    char ** EO = (char **)calloc(n, sizeof(char *));//массив указателей на строки
    //int * num = (int *)calloc(n, sizeof(int));//массив длин строк
    //char ** pEO = EO;//указательна начало двумерного массива

    char ch = 0;

    for(int i = 0; i < n; i++)
    {
        //char * spEO = EO[i];

        EO[i] = (char*)calloc(m, sizeof(char));

        for(int j = 0; j < m && (ch = (char)getc(read)) != '\n'; j++) // && (ch = (char)getc(read)) != '\n'
        {
            EO[i][j] = ch;
        }

    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c", EO[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < n; i++)
        free(EO[i]);

    free(EO);

    return 0;
}
