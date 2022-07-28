#include <stdio.h>
#include <stdlib.h>

int eprimo( int );

int main()
{
    int i;

    for (i=3; i<=1000; i+=2)
    {
        if(eprimo(i) && eprimo(i+2))
        {
            printf("%d e %d sao primos casados\n", i, i+2);
        }
    }

    return 0;
}

int eprimo( int _num)
{
    int i;
    for (i=2; i<_num; i++)
    {
        if(_num%i == 0)
        {
            return 0;
        }
    }
    return 1;
}
