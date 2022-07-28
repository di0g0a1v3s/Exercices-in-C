#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

int main(int arg, char* argv[])
{
    FILE* fp = NULL; //ponteiro para o ficheiro
    int i = 0;
    int n_lines = 0; //numero de linhas (ou palavras do ficheiro)
    char buffer[MAX_STR] = {0}; //string auxiliar
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        printf("Não foi possível abrir o ficheiro\n");
        exit(EXIT_FAILURE);
    }
    char charaux = '0'; //caracter auxiliar
    //ciclo que calcula o número de palavras do ficheiro
    while( charaux != EOF)
    {
        charaux = getc(fp);
        if(charaux == '\n')
            n_lines++;
    }
    //aloca memória para um vetor de ponteiros para cada uma das palavras
    char** lista_palavras = (char**) calloc(n_lines, sizeof(char*));
    if(lista_palavras == NULL)
    {
        printf("Não foi possível alocar memória\n");
        exit(EXIT_FAILURE);
    }


    fclose(fp);
    //volta a abrir o ficheiro, desta vez para procurar a palavra
    fp = fopen("file.txt", "r");

    for(i = 0; i <= n_lines; i++)
    {
        fgets(buffer, MAX_STR, fp); //guarda cada palavra numa variável auxiliar
        *(lista_palavras + i) = (char*) calloc(strlen(buffer), sizeof(char)); //aloca memória para a palavra
        if(*(lista_palavras + i) == NULL)
        {
            printf("Não foi possível alocar memória\n");
            exit(EXIT_FAILURE);
        }
        sscanf(buffer, "%s\n", lista_palavras[i]); //copia a palavra para o sitio correto
        //printf("%s\n", lista_palavras[i]);
    }

    //verifica se a palavra se encontra na lista de palavras em memória
    for(i = 0; i <= n_lines; i++)
    {
        if(strcmp(argv[2], lista_palavras[i]) == 0)
        {
           printf("A palavra encontra-se no ficheiro (linha %d)\n", i + 1);
           exit(EXIT_SUCCESS);
        }
    }
    printf("A palavra não se encontra no ficheiro\n");

    fclose(fp);
    for(i = 0; i < n_lines; i++)
    {
        free(lista_palavras[i]);
    }
    free(lista_palavras);
    return EXIT_SUCCESS;
}
