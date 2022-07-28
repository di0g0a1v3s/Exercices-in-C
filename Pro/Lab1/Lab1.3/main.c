#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define E 2.71828
int main()
{
    float y1 = 0.4f;
    float y2 = 1.2f;
    float y3 = 1.9f;
    float y4 = 2.3f;
    float y5 = 3.5f;

    printf("e^-%f*sin(4*%f) = %f\n", y1, y1, powf(E,-y1) * sin(4*y1) );
    printf("e^-%f*sin(4*%f) = %f\n", y2, y2, powf(E,-y2) * sin(4*y2) );
    printf("e^-%f*sin(4*%f) = %f\n", y3, y3, powf(E,-y3) * sin(4*y3) );
    printf("e^-%f*sin(4*%f) = %f\n", y4, y4, powf(E,-y4) * sin(4*y4) );
    printf("e^-%f*sin(4*%f) = %f\n", y5, y5, powf(E,-y5) * sin(4*y5) );
    return 0;
}
