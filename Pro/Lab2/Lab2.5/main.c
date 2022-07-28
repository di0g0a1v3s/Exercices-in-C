#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void adivinhanumero(int, int, int*, int*);
int main()
{

    srandom(time(NULL));
    int n = 1000;
    int m = 10;
    int resultado = 0;
    int tentativas = 0;
    printf("O computador irá tentar adivinhar um numero aleatório entre 1 e %d, tem %d tentativas:\n",n,m);
    adivinhanumero(n, m, &resultado, &tentativas);
    if(resultado == 1)
        printf("Parabéns! Acertou o número em %d tentativas", tentativas);
    else
        printf("O computador não acertou no número :\(");
    return 0;
}


void adivinhanumero(int _n, int _m, int* _resultado, int* _tentativas)
{

    int number = random()%_n + 1;
    int n_inserido = 0;
    int clue = 0;
    int biggerthan = 1;
    int smallerthan = _n;
    *_tentativas = 0;
    *_resultado = 0;
    while( *_tentativas < _m)
    {
        n_inserido = (biggerthan + smallerthan)/2;
        printf("%d\n", n_inserido);

        *_tentativas = *_tentativas + 1;
        if(n_inserido == number)
        {
            *_resultado = 1;
            return;
        }
        else if(number > n_inserido)
        {
            printf("O número pretendido é maior\n");
            clue = -1;
        }
        else{
            printf("O número pretendido é menor\n");
            clue = 1;
        }

        if(clue == 1)
        {
            smallerthan = n_inserido;
        }
        else if (clue == -1)
            biggerthan = n_inserido;

    }
    return;
}
