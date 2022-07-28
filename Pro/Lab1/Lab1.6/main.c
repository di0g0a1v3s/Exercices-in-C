#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ano;
    printf("Introduza um ano: ");
    scanf("%d", &ano);

    if(ano%400 == 0)
        printf("O ano tem 366 dias");
    else if(ano%100 == 0)
        printf("O ano tem 365 dias");
    else if(ano%4 == 0)
        printf("O ano tem 366 dias");
    else
        printf("O ano tem 365 dias");
    return 0;
}
