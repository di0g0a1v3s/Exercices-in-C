#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 100
#define MAX_N 10

void load_vect(char[MAX_N][MAX_STR_SIZE], int);
void sort_vect(char[MAX_N][MAX_STR_SIZE], int);
void print_vect(char[MAX_N][MAX_STR_SIZE], int);

int main()
{
    int n;
    char str_vect[MAX_N][MAX_STR_SIZE];
    do{
        printf("Insira a quantidade de palavras a serem lidas:(1-10) ");
        scanf("%d",&n);
    }while(n > 10 || n < 1);

    load_vect(str_vect, n);
    sort_vect(str_vect, n);
    printf("\n");
    print_vect(str_vect, n);

    return 0;
}

void load_vect(char _str_vect[MAX_N][MAX_STR_SIZE], int _n)
{
    int i;
    printf("Insira as palavras:\n");
    for(i = 0; i < _n; i++)
    {
        fgets(_str_vect[i], MAX_STR_SIZE, stdin);
    }
}
void sort_vect(char _str_vect[MAX_N][MAX_STR_SIZE], int _n)
{
    int i;
    int j;
    char aux[MAX_STR_SIZE];

    for(i = 0; i < _n; i++)
    {
        for(j=i; j<_n; j++)
        {
            if(strcmp(_str_vect[i], _str_vect[j]) > 0)
            {
                strcpy(aux, _str_vect[i]);
                strcpy(_str_vect[i], _str_vect[j]);
                strcpy(_str_vect[j], aux);
            }
        }

    }
}

void print_vect(char _str_vect[MAX_N][MAX_STR_SIZE], int _n)
{
    int i;
    printf("Ordem alfabetica:\n");
    for(i = 0; i < _n; i++)
    {
        printf("%s", _str_vect[i]);
    }
}
