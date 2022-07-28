#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

typedef struct node{
    char *str;
    struct node *next;
}node_t;

node_t* populate_list(char* ficheiro_palavras);
void procurar_palavra(node_t *head, char* palavra_a_procurar);
void free_list(node_t *head);

int main(int arg, char* argv[])
{
    node_t* head = NULL;
    char* ficheiro_palavras = argv[1];
    char* palavra_a_procurar = argv[2];

    head = populate_list(ficheiro_palavras);
    procurar_palavra(head, palavra_a_procurar);
    free_list(head);
    return EXIT_SUCCESS;
}

node_t* populate_list(char* ficheiro_palavras)
{
    FILE* fp = fopen(ficheiro_palavras, "r");
    node_t *head = NULL;
    node_t *current = NULL;
    char buffer[MAX_STR];
    if(fp == NULL)
    {
        printf("Não foi possível abrir o ficheiro");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, MAX_STR, fp) != NULL)
    {
        if(head == NULL)
        {
            head = (node_t*)calloc(1, sizeof(node_t));
            head->next = NULL;
            head->str = (char*)calloc(strlen(buffer) + 1, sizeof(char));
            sscanf(buffer, "%s\n", head->str);
            current = head;

        }
        else
        {
            current->next = (node_t*)calloc(1, sizeof(node_t));
            current = current->next;
            current->str = (char*)calloc(strlen(buffer) + 1, sizeof(char));
            sscanf(buffer, "%s\n", current->str);
            current->next = NULL;

        }
       // printf("%s\n", current->str);
    }
    fclose(fp);
    return head;

}


void procurar_palavra(node_t *head, char* palavra_a_procurar)
{
    node_t *current = head;

    do
    {
        if(strcmp(current->str, palavra_a_procurar)==0)
        {
            printf("A palavra encontra-se no ficheiro\n");
            return;
        }
        current = current->next;

    }while(current != NULL);

    printf("A palavra não se encontra no ficheiro\n");
}

void free_list(node_t *head)
{
    node_t *current = head;

    while(head->next != NULL)
    {
        while(current->next->next != NULL)
            current = current->next;

        free(current->next->str);
        free(current->next);
        current->next = NULL;

        current = head;
    }

    free(head->str);
    free(head);


}
