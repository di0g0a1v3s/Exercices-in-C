#include  <stdlib.h>
#include  <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define READ 0
#define WRITE 1
#define NUMBER_THREADS 4

int number_count[NUMBER_THREADS];
int** fd_array;

int isMultipleOf(int number, int of)
{
  if(number%of == 0)
    return 1;
  return 0;
}

void *thread_func (void* arg)
{
  int thread_number = *(int*) arg;
  int value;

  if(thread_number == 0)
    value = 2;
  else if(thread_number == 1)
    value = 3;
  else if(thread_number == 2)
    value = 5;
  else if(thread_number == 3)
    value = 7;

  int number_read = 0;
  while(read(fd_array[thread_number][READ], &number_read, sizeof(int)) != 0)
  {
    if(isMultipleOf(number_read, value))
      number_count[thread_number]++;
  }
  return 0;

}

int main()
{
  int ret = 0;
  int number = 0;
  pthread_t thread_id;
  pthread_t thread_ids[NUMBER_THREADS];
  int args[NUMBER_THREADS] = {0,1,2,3};
  int i = 0;
  //4 pipes
  fd_array = (int**) malloc(NUMBER_THREADS * sizeof(int*));
  for(i = 0; i < NUMBER_THREADS; i++)
	{
		fd_array[i] = (int*) malloc(sizeof(int)*2);
		if (pipe(fd_array[i]) == -1)
	  {
	    printf("Failed to create pipe\n");
			return 1;
		}
	}


  for(i = 0; i < NUMBER_THREADS; i++)
	{

    pthread_create(&thread_id, NULL, thread_func, &(args[i]));
    thread_ids[i] = thread_id;
  }

  do{
    ret = scanf("%d", &number);
    if(number >= 0 && ret == 1)
    {
      for(i = 0; i < NUMBER_THREADS; i++)
        write(fd_array[i][WRITE], &number, sizeof(int));
    }
  }while(number >= 0);

  for (i = 0; i < NUMBER_THREADS; i++)
  {
    close(fd_array[i][WRITE]);  // Close writing end of pipes
  }

  for (i = 0; i < NUMBER_THREADS; i++)
  {
    pthread_join(thread_ids[i], NULL);
  }

  for (i = 0; i < NUMBER_THREADS; i++)
  {
    close(fd_array[i][READ]);  // Close reading end of pipes
  }

  printf("MULTIPLES OF 2: %d\n", number_count[0]);
  printf("MULTIPLES OF 3: %d\n", number_count[1]);
  printf("MULTIPLES OF 5: %d\n", number_count[2]);
  printf("MULTIPLES OF 7: %d\n", number_count[3]);

  for(i = 0; i < NUMBER_THREADS; i++)
	{
		free(fd_array[i]);
  }
  free(fd_array);

}
