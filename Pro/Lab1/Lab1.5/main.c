#include <stdio.h>
#include <stdlib.h>

int main()
{
    char caracter;
    printf("Introduza um caracter: ");
    scanf("%c", &caracter);

    // a...z - 97...122, A..Z - 65...90, 0...9 - 48...57
    if((caracter>=97 && caracter<=122) || (caracter>=65 && caracter<=90)){
       printf("\nO caracter é uma letra\n");
        if(caracter == 'A' || caracter == 'E' || caracter == 'I' || caracter == 'O' || caracter == 'U' ||
           caracter == 'a' || caracter == 'e' || caracter == 'i' || caracter == 'o' || caracter == 'u')
            printf("\nA letra é uma vogal\n");
        else
            {printf("\nA letra é uma consoante\n");
            if((caracter>=97 && caracter<=122))
                printf("\nA consoante está escrita em letra minúscula\n");
            else
                printf("\nA consoante está escrita em letra maiúscula\n");}
       }
       else if(caracter>=48 && caracter<=97)
        printf("\nO caracter é um número\n");
       else
        printf("\nO caracter é um caracter especial\n");

    return 0;
}
