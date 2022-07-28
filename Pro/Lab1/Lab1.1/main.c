#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    int main(void){
    /*  calcula maior raiz de ax^2 + bx + c = 0, a>=0 */
        float a, b, c, discr;
        printf("Escreva os valores de a (>=0), b e c: ");
        scanf("%f %f %f", &a, &b, &c);
        discr = b*b -4*a*c;
        if(discr < 0)
            printf("Raizes complexas !\n");
        else
            printf("Maior raiz = %f\n", (-b + sqrt(discr))/(2*a) );
        return EXIT_SUCCESS;
}
