#include <stdio.h>
#include <stdlib.h>


int evalido(long int);

int main()
{
    long int ticket;
    printf("Insira o numero do bilhete:\n");
    scanf("%ld", &ticket);
    printf("%d",sizeof(long int));
    if(evalido(ticket))
        printf("O bilhete é valido");
    else printf("O bilhete não é válido");
    return 0;
}

int evalido(long int _ticket)
{
    if((_ticket/10)%7 == _ticket%10)
    {
        return 1;
    }
    else return 0;
}
