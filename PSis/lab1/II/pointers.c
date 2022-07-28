#include <stdlib.h>
#include <math.h>

int a;

int main(){
    int b;
    char v[10];
    double (*func)(double x);
    func = sin;


    char *p = malloc(1);


    printf("&a -    %p\n", &a);
    printf("&b -    %p\n", &b);

    printf("v -     %p\n", v);
    printf("&v -    %p\n", &v);

    printf("&main - %p\n", main);
    printf("&exit - %p\n", exit);
    printf("sin -   %p\n", sin);
    printf("&sin -  %p\n", &sin);
    printf("func -  %p\n", func);
    printf("&func - %p\n", &func);


    printf("&p -    %p\n", &p);

    printf("p -     %p\n", p);



    exit(0);


}
