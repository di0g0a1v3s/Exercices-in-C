#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SieveOfErathostenes(int);
void FlagMultipleNumbers(int, int, int*);

int main()
{
    int limit = 0;

    printf("Insira um numero inteiro:\n");
    scanf("%d", &limit);
    printf("Primos:\n");
    SieveOfErathostenes(limit);


    return 0;
}


void SieveOfErathostenes(int _limit)
{
    int i;
    int lista[_limit + 1];
    for (i = 0; i <= _limit; i++)
    {
        lista[i] = i;
    }
    lista[1] = 0;

    for(i=2; i<=sqrt(_limit);i++)
    {
        if(lista[i] != 0) FlagMultipleNumbers(i, _limit, &lista[0]);
    }

    for (i = 0; i <= _limit; i++)
    {
        if(lista[i] != 0) printf("%d\n",lista[i]);
    }
}


void FlagMultipleNumbers(int _i, int _limit, int* _lista)
{
    int i;
    for(i = 2*_i; i <= _limit; i = i + _i)
    {
        _lista[i] = 0;
    }
}
