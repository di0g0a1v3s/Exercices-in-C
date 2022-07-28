#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct ISTPerson{
    int ist_id;
    char nome[MAX];
    char dominio[MAX];
    int ano_nascimento;
};

struct ISTPerson* criar_vetor(int* contagem_pessoas, char* ficheiro_pessoas);
void imprimir_velho_novo(struct ISTPerson* pessoas, int contagem_pessoas);

int main()
{
    struct ISTPerson *pessoas = NULL;
    int contagem_pessoas = 0;
    char ficheiro_pessoas[] = "file.txt";

    pessoas = criar_vetor(&contagem_pessoas, ficheiro_pessoas);
    imprimir_velho_novo(pessoas, contagem_pessoas);

    free(pessoas);

    return 0;
}

struct ISTPerson* criar_vetor(int* contagem_pessoas, char* ficheiro_pessoas)
{
    char cardinal[] = "#";
    char *token = NULL;
    char *p_aux = NULL;
    char buffer[MAX];
    FILE *fp = fopen(ficheiro_pessoas, "r");
    struct ISTPerson *pessoas = NULL;

    if(fp == NULL)
    {
        printf("Não foi possivel abrir o ficheiro\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, MAX, fp) != NULL)
    {
        pessoas = (struct ISTPerson*)realloc(pessoas, (*contagem_pessoas+1)*sizeof(struct ISTPerson));
        if(pessoas == NULL)
        {
            printf("Não foi possivel alocar memória\n");
            exit(EXIT_FAILURE);
        }

        token = strtok(buffer, cardinal);
        sscanf(token, "ist%d", &(pessoas[*contagem_pessoas].ist_id));
        token = strtok(NULL, cardinal);
        p_aux = strchr(token, '@');
        *p_aux = '\0';
        p_aux++;
        strcpy(pessoas[*contagem_pessoas].nome, token);
        strcpy(pessoas[*contagem_pessoas].dominio, p_aux);
        token = strtok(NULL, cardinal);
        sscanf(token, "%d", &(pessoas[*contagem_pessoas].ano_nascimento));

        (*contagem_pessoas)++;

    }

    fclose(fp);
    return pessoas;
}

void imprimir_velho_novo(struct ISTPerson* pessoas, int contagem_pessoas)
{
    int mais_antigo = 0;
    int mais_novo = 0;
    int menor_ano_nasc = 0;
    int maior_ano_nasc = 0;
    for(int i = 0; i < contagem_pessoas; i++)
    {
        if(maior_ano_nasc < pessoas[i].ano_nascimento)
        {
            maior_ano_nasc = pessoas[i].ano_nascimento;
            mais_novo = i;
        }

        if(menor_ano_nasc == 0)
            menor_ano_nasc = pessoas[i].ano_nascimento;

        if(menor_ano_nasc > pessoas[i].ano_nascimento)
        {
            menor_ano_nasc = pessoas[i].ano_nascimento;
            mais_antigo = i;
        }
    }
    printf("Funcionário mais velho:\nID: ist%d\tEmail: %s@%s\n\nFuncionário mais novo:\nID: ist%d\tEmail: %s@%s\n",
           pessoas[mais_antigo].ist_id, pessoas[mais_antigo].nome, pessoas[mais_antigo].dominio,
           pessoas[mais_novo].ist_id, pessoas[mais_novo].nome, pessoas[mais_novo].dominio);
}
