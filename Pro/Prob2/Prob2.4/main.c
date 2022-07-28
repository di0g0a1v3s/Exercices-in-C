#include <stdio.h>
#include <stdlib.h>

int main()
{
    int altura = 0;
    int i = 1;
    int i2 = 1;
    int incremento = 1;
    printf("Insira a altura do triangulo:\n");
    scanf("%d", &altura);
    printf("\n");
    for(i = 1; i != 0; i = i + incremento){
        for(i2 = 1; i2 <= i; i2++) printf("* ");

        printf("\n");

        if(i == altura) incremento = -1;
    }

    return 0;
}
