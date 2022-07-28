#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _r
{
    char *sss;
    struct _r *next;
}t_r;

void f1(t_r **n, char *str)
{
    t_r *a;
    a = (t_r*)calloc(1, sizeof(t_r));
    if(a == NULL)
        exit(1);
    a->sss = str;
    a->next = (*n);
    *n = a;
}

int main()
{
    char s1[] = "1234567890";
    t_r *k;

    f1(&k, s1);
    f1(&k, s1+2);
    f1(&k, s1+5);

    while(k != NULL)
    {
        printf("%s\n", k->sss);
        k = k->next;
    }
    exit(0);
}
