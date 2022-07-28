#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** criar_matriz(int);
void imprimir_matriz(int**, int);

int main()
{
    srand(time(NULL));
    int tamanho_matriz = 0;
    int i = 0;
    int j = 0;

    printf("Introduza o tamanho da matriz: ");
    scanf("%d", &tamanho_matriz);
    //aloca memória para as matrizes
    int **matriz = criar_matriz(tamanho_matriz);
    int **matriz_soma = criar_matriz(tamanho_matriz);
    //preenche a matriz com números entre 1 e 8
    for(i = 0; i < tamanho_matriz; i++)
    {
        for(j = 0; j < tamanho_matriz; j++)
        {
            matriz[i][j] = rand()%8 + 1;
        }
    }
    //preenche a matriz soma
    criar_soma(matriz, matriz_soma, tamanho_matriz);
    //imprime as matrizes
    imprimir_matriz(matriz, tamanho_matriz);
    printf("\n\n");
    imprimir_matriz(matriz_soma, tamanho_matriz);

    for(i = 0; i<tamanho_matriz; i++)
    {
        free(matriz[i]);
        free(matriz_soma[i]);
    }
    free(matriz);
    free(matriz_soma);
    return 0;
}

int** criar_matriz(int _tamanho_matriz)
{
    int i = 0;
    int **matriz = (int**) calloc(_tamanho_matriz, sizeof(int*)); //aloca espaço para um vetor que terá o endreços das linhas
    if(matriz == NULL)
    {
        printf("Não foi possível alocar memória\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < _tamanho_matriz; i++)
    {
        *(matriz + i) = (int*) calloc(_tamanho_matriz, sizeof(int)); //aloca espaço para cada linha
        if(*(matriz + i) == NULL)
        {
            printf("Não foi possível alocar memória\n");
            exit(EXIT_FAILURE);
        }
    }
    return matriz;
}

void imprimir_matriz(int** _matriz, int _tamanho_matriz)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < _tamanho_matriz; i++)
    {
        for(j = 0; j < _tamanho_matriz; j++)
        {
            printf("%d | ", _matriz[i][j]);
        }
        printf("\n");
    }
}

void criar_soma(int** _matriz, int** _matriz_soma, int _tamanho_matriz)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < _tamanho_matriz; i++)
    {
        for(j = 0; j < _tamanho_matriz; j++)
        {
            if(i == 0 || j == 0 || i == _tamanho_matriz - 1 || j == _tamanho_matriz - 1)
            {
                _matriz_soma[i][j] = 0;
            }
            else
            {
                //soma os valores necessários
                _matriz_soma[i][j] = _matriz[i][j] + _matriz[i][j - 1] + _matriz[i][j + 1] + _matriz[i - 1][j] + _matriz[i + 1][j];
            }
        }
    }
}
