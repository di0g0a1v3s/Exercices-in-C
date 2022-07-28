#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

typedef struct phoneEntry
{
    char *nome;
    int phonenum;
    struct phoneEntry* next;

}phoneEntry;

void load_phonebook(FILE*, phoneEntry**);
void print_number(phoneEntry*, char*);
void sort_phonebook(phoneEntry*);

int main()
{
    FILE *fp = fopen("phonebook.txt", "r"); //ponteiro para o ficheiro
    if(fp == NULL)
    {
        printf("Não foi possível abrir o ficheiro\n");
        exit(EXIT_FAILURE);
    }

    phoneEntry* phonebook = NULL;

    load_phonebook(fp, &phonebook);
    print_number(phonebook, "io");
    sort_phonebook(phonebook);
    return 0;
}

void load_phonebook(FILE *fp, phoneEntry **phonebook)
{
    int i = 0;
    int n_lines = 0; //numero de linhas do ficheiro
    char buffer[MAX_STR] = {0}; //string auxiliar
    char buffer2[MAX_STR] = {0};
    char charaux = '0'; //caracter auxiliar
    //ciclo que calcula o número de linhas do ficheiro
    while( charaux != EOF)
    {
        charaux = getc(fp);
        if(charaux == '\n')
            n_lines++;
    }
    //aloca memória para um vetor de ponteiros para cada uma das palavras
    *phonebook = (phoneEntry*) calloc(n_lines + 1, sizeof(phoneEntry));
    if(*phonebook == NULL)
    {
        printf("Não foi possível alocar memória\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    //volta a abrir o ficheiro, desta vez para procurar a palavra
    fp = fopen("phonebook.txt", "r");

    for(i = 0; i <= n_lines; i++)
    {
        fgets(buffer, MAX_STR, fp); //guarda cada conjunto nome,telefone numa variável auxiliar
        sscanf(buffer, "%s %d\n", buffer2, &(((*phonebook)[i]).phonenum));
        (((*phonebook)[i]).nome) = (char*) calloc(strlen(buffer2) + 1, sizeof(char)); //aloca memória para o nome
        if((((*phonebook)[i]).nome) == NULL)
        {
            printf("Não foi possível alocar memória\n");
            exit(EXIT_FAILURE);
        }
        sscanf(buffer2, "%s", (((*phonebook)[i]).nome)); //copia o nome para o sitio correto
        printf("%s ", (*phonebook)[i].nome);
        printf("%d\n", (*phonebook)[i].phonenum);
        (*phonebook)[i].next = NULL;
        if(i > 0)
        {
            ((*phonebook)[i-1]).next = &(*(phonebook)[i]);

        }


    }
}

void print_number(phoneEntry *phonebook, char *pname)
{
    int i = 0;
    printf("\n");
    while(phonebook[i-1].next != NULL)
    {
        if(strstr(phonebook[i].nome, pname) != NULL)
        {
            printf("%s ", phonebook[i].nome);
            printf("%d\n", phonebook[i].phonenum);
        }
        i++;
    }

}

void sort_phonebook(phoneEntry *phonebook)
{
    int i = 0;
    int j = 0;
    phoneEntry aux;
    for(i = 0; phonebook[i].next != NULL; i++)
    {
        for(j = i + 1; phonebook[j].next != NULL; j++)
        if(strcmp(phonebook[i].nome, phonebook[j].nome) < 0)
        {
            aux.phonenum = phonebook[i].phonenum;
            aux.nome = phonebook[i].nome;
            aux.next = phonebook[i].next;
            phonebook[i].phonenum = phonebook[j].phonenum;
            phonebook[i].nome = phonebook[j].nome;
            phonebook[i].next = phonebook[j].next;
            phonebook[j].phonenum = aux.phonenum;
            phonebook[j].nome = aux.nome;
            phonebook[j].next = aux.next;

        }

    }
    i = 0;

        while(phonebook[i-1].next != NULL)
        {
            printf("%s %d\n", phonebook[i].nome, phonebook[i].phonenum);
            i++;
        }

}

