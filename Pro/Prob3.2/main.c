#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIX_SIZE 10

void load_mat(int[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int, int);
void sum_mat(int[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int, int);
void print_mat(int[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int, int);

int main()
{
    int n;
    int m;
    int mat1[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    int mat2[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    do{
        printf("Insira as dimensoes das matrizes:(1-10) ");
        scanf("%dx%d",&n, &m);
    }while(n > 10 || n < 1 || m > 10 || m < 1);

    load_mat(mat1, n, m);
    load_mat(mat2, n, m);

    sum_mat(mat1, mat2, n, m);

    print_mat(mat1, n, m);

    return 0;
}

void load_mat(int mat[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int _n, int _m)
{
    int i;
    int j;
    printf("Insira os elementos da matriz:\n");
    for(i = 0; i < _n; i++)
    {
        for(j = 0; j < _m; j++)
        {
           printf("Elemento %d,%d: ",i+1,j+1);
           scanf("%d", &mat[i][j]);
        }

    }
}
void sum_mat(int mat1[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int mat2[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int _n, int _m)
{
    int i;
    int j;

    for(i = 0; i < _n; i++)
    {
        for(j=0; j<_m; j++)
        {
            mat1[i][j] += mat2[i][j];
        }

    }
}

void print_mat(int mat[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int _n, int _m)
{
    int i;
    int j;
    printf("Soma: \n");
    for(i = 0; i < _n; i++)
    {
        for(j=0; j<_m; j++)
        {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}
