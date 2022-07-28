#include <stdio.h>
#include <stdlib.h>

int main()
{
    float nota;
    printf("Insira uma nota: ");
    scanf("%f", &nota);
    if(nota > 4)
        printf("Nota inválida");
    else if (nota == 4)
        printf("A+");
    else if (nota > 3.7)
        printf("A");
    else if (nota > 3.3)
        printf("A-");
    else if (nota > 3.0)
        printf("B+");
    else if (nota > 2.7)
        printf("B");
    else if (nota > 2.3)
        printf("B-");
    else if (nota > 2.0)
        printf("C+");
    else if (nota > 1.7)
        printf("C");
    else if (nota > 1.3)
        printf("C-");
    else if (nota > 1.0)
        printf("D+");
    else if (nota > 0.7)
        printf("D");
    else if (nota >= 0)
        printf("F");
    else printf("Nota inválida");

}
