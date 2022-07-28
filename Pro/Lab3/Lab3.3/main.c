#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

struct model
{
    char model_char;
    int model_int;
};

struct plane
{
    int airplaneID;
    struct model model;
    float fuel;
};

void readPlanes(struct plane **, int*);
int lowestFuel(struct plane*, int);
void printID(struct plane*, int, char*);

int main()
{
    struct plane *planes;
    int size;
    readPlanes(&planes, &size);

    int lowest_plane = lowestFuel(planes, size);
    printf("O avião com menos combustível tem o ID %d, é o modelo %c%d e tem %.2f combustível\n",
           planes[lowest_plane].airplaneID, planes[lowest_plane].model.model_char, planes[lowest_plane].model.model_int, planes[lowest_plane].fuel);
    printf("Insira um modelo: ");

    char model[MAX_STR];
    fgets(model, MAX_STR, stdin);
    printID(planes, size, model);
}

void readPlanes(struct plane **planes, int *size)
{
    int i = 0;
    char buffer[MAX_STR];
    printf("Insira o número de aviões: ");
    fgets(buffer, MAX_STR, stdin);
    sscanf(buffer,"%d", size);
    *planes = (struct plane*)calloc(*size, sizeof(struct plane));

    for(i = 0; i < *size; i++)
    {
        printf("%dº avião:\n", i+1);
        printf("ID: ");
        fgets(buffer, MAX_STR, stdin);
        sscanf(buffer,"%d", &((*planes + i)->airplaneID));
        printf("Modelo: ");
        fgets(buffer, MAX_STR, stdin);
        sscanf(buffer,"%c%d", &((*planes + i)->model.model_char), &((*planes + i)->model.model_int));
        printf("Combustivel: ");
        fgets(buffer, MAX_STR, stdin);
        sscanf(buffer,"%f", &((*planes + i)->fuel));
    }

}

int lowestFuel(struct plane *planes, int size)
{
    int i = 0;
    float lowestfuel = planes[0].fuel;
    int lowest_plane = 0;
    for(i = 1; i < size; i++)
    {
        if(planes[i].fuel < lowestfuel)
        {
            lowestfuel = planes[i].fuel;
            lowest_plane = i;
        }
    }
    return lowest_plane;
}

void printID(struct plane* planes, int size, char* model)
{
    int i = 0;
    char model_char;
    int model_int;
    for(i = 0; i < size; i++)
    {
        sscanf(model,"%c%d", &model_char, &model_int);
        if(planes[i].model.model_char == model_char && planes[i].model.model_int == model_int)
        {
            printf("O avião %d tem o modelo %s\n", planes[i].airplaneID, model);
        }
    }
}
