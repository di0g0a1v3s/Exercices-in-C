#include <stdio.h>
#include <stdlib.h>

int main()
{
    long int a,b;
    a = 0;
    b = 0;
    printf("Introduza dois números inteiros:\n");
    scanf("%lu", &a);
    scanf("%lu", &b);
    if (a == b)
        printf("Os números são iguais");
    else if (a < b)
        printf("O maior número é %lu", b);
    else
        printf("O maior número é %lu", a);


    return 0;
}
