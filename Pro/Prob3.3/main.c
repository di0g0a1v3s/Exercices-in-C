#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 500

int main()
{
    char input[MAX_STR];
    char ficheiro[MAX_STR];
    char palavra[MAX_STR];
    char buff[MAX_STR];
    int linha = 1;
    int i = 0;

    fgets(input, MAX_STR, stdin);
    sscanf(input,"%s %s", ficheiro, palavra);

    FILE *fp = NULL;
    fp = fopen(ficheiro, "r");


    if(fp == NULL)
    {
        printf("O ficheiro não foi aberto corretamente");
        exit(EXIT_FAILURE);
    }

    do
    {
        fgets(buff, 500, fp);
        if(strstr(buff, palavra) != NULL)
        {
            printf("%d\n", linha);
        }
        linha++;




    }while(fgetc(fp) != EOF);

    return 0;
}
