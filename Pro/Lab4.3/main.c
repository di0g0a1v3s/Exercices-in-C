#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int n;
    struct node* next;
    struct node* previous;
}node_t;

node_t* gerar_numeros(int number_of_elements);
void free_list(node_t *head);

int main()
{
    int number_of_elements = 0;
    int number_of_zeros = 0;
    int number_of_ones = 0;
    node_t *head = NULL;
    srand(time(NULL));
    printf("Insira o número de elementos a serem gerados:\n");
    scanf("%d", &number_of_elements);
    head = gerar_numeros(number_of_elements);

    node_t *current = head;
    while(current != NULL)
    {
        if(current->n == 0)
            number_of_zeros++;
        else
            number_of_ones++;
        current = current->next;
    }
    printf("Número de zeros = %d\n", number_of_zeros);
    printf("Número de uns = %d\n", number_of_ones);
    free_list(head);
    return 0;
}

node_t* gerar_numeros(int number_of_elements)
{
    int i = 0;
    int rand_num = 0;
    node_t *head = NULL;
    node_t *new_node = NULL;
    for(i = 0; i < number_of_elements; i++)
    {
        if(head == NULL)
        {
            head = (node_t*)calloc(1, sizeof(node_t));
            if(head == NULL)
            {
                printf("Não foi possivel alocar memória");
                exit(EXIT_FAILURE);
            }

            head->n = rand()%2;
            head->next = NULL;
            head->previous = NULL;
        }
        else
        {
            rand_num = rand()%2;
            if(rand_num == 0)
            {
                new_node = (node_t*)calloc(1, sizeof(node_t));
                if(new_node == NULL)
                {
                    printf("Não foi possivel alocar memória");
                    exit(EXIT_FAILURE);
                }
                new_node->n = rand_num;
                head->previous = new_node;
                new_node->next = head;
                new_node->previous = NULL;
                head = new_node;
            }
            else if(rand_num == 1)
            {
                new_node = head;
                while(new_node->next != NULL)
                    new_node = new_node->next;
                new_node->next = (node_t*)calloc(1, sizeof(node_t));
                if(new_node == NULL)
                {
                    printf("Não foi possivel alocar memória");
                    exit(EXIT_FAILURE);
                }
                new_node->next->n = rand_num;
                new_node->next->next = NULL;
                new_node->next->previous = new_node;

            }
        }

    }
    return head;
}

void free_list(node_t *head)
{
    while(head->next != NULL)
    {
        head = head->next;
        free(head->previous);
    }
    free(head);
}
