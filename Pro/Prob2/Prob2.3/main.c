#include <stdio.h>
#include <stdlib.h>

int main()
{
    int mes = 0;



    do{
        printf("\nInsira um mês (1-12)\n");
        scanf("%d", &mes);
        switch(mes){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                printf("31 dias");
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                printf("30 dias");
                break;
            case 2:
                printf("29 dias");
                break;
            default :
                printf("Número fora da gama de valores");}

    }while(mes>=1 && mes<=12);

    return 0;
}
