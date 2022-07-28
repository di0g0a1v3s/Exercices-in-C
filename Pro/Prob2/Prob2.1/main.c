#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number = 0;
    int i = 0;

    do{
        printf("Insira um número natural:\n");
        scanf("%d", &number);
            if(number < 0) printf("Número não natural\n");
    }while(number < 0);

    for(i = 1; i <= number; i++){
        if(number%i == 0) printf("%d é divisor de %d\n",i,number);
    }
    return 0;
}
