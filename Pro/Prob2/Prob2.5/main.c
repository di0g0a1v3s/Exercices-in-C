#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num0 = 0;
    int num1 = 0;
    int cresc = 0;
    int decr = 0;
    int numin = 0;
    printf("Insira uma sequência de numeros (-1 para sair):\n");

    scanf("%d", &numin);
    num1 = numin;
    while (numin != -1){
        scanf("%d", &numin);
        if (numin == -1) break;
        num0 = num1;
        num1 = numin;
        if(num0 > num1) decr = 1;
        else if(num1 > num0) cresc = 1;
    }
        if(decr == 1 && cresc == 1) printf("Mista");
        else if(decr == 1) printf("Decrescente");
        else if(cresc == 1) printf("Crescente");
        else printf("Nem crescente nem decrescente");

    return 0;
}
