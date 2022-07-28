#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void adivinhanumero(int, int, int*, int*);
int main()
{

    srandom(time(NULL));
    int n = 20;
    int m = 5;
    int resultado = 0;
    int tentativas = 0;
    printf("Adivinhe o numero entre 1 e %d, tem %d tentativas:\n",n,m);
    adivinhanumero(n, m, &resultado, &tentativas);
    if(resultado == 1)
        printf("Parabéns! Acertou o número em %d tentativas", tentativas);
    else
        printf("Você não acertou no número :\(");
    return 0;
}


void adivinhanumero(int _n, int _m, int* _resultado, int* _tentativas)
{

    int number = random()%_n + 1;
    int n_inserido = 0;
    *_tentativas = 0;
    *_resultado = 0;
    while( *_tentativas < _m)
    {
        scanf("%d",&n_inserido);
        *_tentativas = *_tentativas + 1;
        if(n_inserido == number)
        {
            *_resultado = 1;
            return;
        }
        else if(number > n_inserido)
        {
            printf("O número pretendido é maior\n");
        }
        else{
            printf("O número pretendido é menor\n");
        }

    }
    return;
}
