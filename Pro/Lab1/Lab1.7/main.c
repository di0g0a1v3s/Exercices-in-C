#include <stdio.h>
#include <stdlib.h>

int main()
{
    char coluna;
    int linha;

    //a...h - 97...104

    printf("Coluna (a...h): ");
    scanf("%c", &coluna);
    if(!(coluna>=97 && coluna<=104)){
        printf("Coluna inválida");
        return EXIT_FAILURE;}

    printf("Linha (1...8): ");
    scanf("%d", &linha);
    if(!(linha>=1 && linha<=8)){
        printf("Linha inválida");
        return EXIT_FAILURE;}

    int coluna_int = coluna - 96;
    int linha_int = linha;

    //o mosaico é branco se for coluna par e linha impar ou linha par e coluna impar, ie, linha+coluna impar

    if((linha_int + coluna_int)%2 != 0)
        printf("Quadrado Branco");
    else
        printf("Quadrado Preto");
    return 0;
}
