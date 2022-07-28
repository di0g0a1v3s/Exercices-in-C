#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    char string[100] = "";
    printf("Insira um conjunto de caracteres:\n");
    scanf("%s", string);
    printf("\n");

    for(i = 0; i <= 99; i++){

       if(string[i] >= 97 && string[i] <= 122){
            string[i] = string[i] - 32;}


    }
        printf("%s",string);
    return 0;
}
