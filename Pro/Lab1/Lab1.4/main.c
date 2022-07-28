#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float centrox, centroy, centroz, raio, pontox, pontoy, pontoz;

    printf("Centro:\nX = ");
    scanf("%f", &centrox);
    printf("Y = ");
    scanf("%f",&centroy);
    printf("Z = ");
    scanf("%f",&centroz);

    printf("\nRaio = ");
    scanf("%f",&raio);

    printf("\nÁrea = %f\nVolume = %f", 4*M_PI*pow(raio,2), (4.0/3.0)*M_PI*pow(raio,2));

    printf("\n\nPonto:\nX = ");
    scanf("%f", &pontox);
    printf("Y = ");
    scanf("%f",&pontoy);
    printf("Z = ");
    scanf("%f",&pontoz);

    float dist_centro = sqrt( pow((centrox-pontox),2) + pow((centroy-pontoy),2) + pow((centroz-pontoz),2) );
    //printf("%f\n\n",dist_centro);

    if( dist_centro <= raio)
        printf("O ponto está dentro da esfera");
    else
        printf("O ponto está fora da esfera");

    return 0;
}
