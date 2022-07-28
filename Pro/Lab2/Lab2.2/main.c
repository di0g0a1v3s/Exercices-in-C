#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char digito(int, int);

int main()
{
    int n;
    int i = 1;
    printf("Insira um número inteiro posistivo:\n");
    scanf("%d", &n);

    int n_digits = 0;
    int aux = n;
    while(aux != 0)
    {
        aux = aux/10;
        n_digits++;
    }

    while(i<=n_digits)
    {
        printf("%dº digito: %c\n",i,digito(i,n));
        i++;
    }
    return 0;
}

char digito( int _k, int _n)
{
    int n_digits = 0;
    int aux = _n;
    while(aux != 0)
    {
        aux = aux/10;
        n_digits++;
    }

    char digit = (_n/(int)pow(10, n_digits - _k))%(10) + '0';
    return digit;
}
