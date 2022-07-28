#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func (void * arg){
  int n = 0;
  if(arg != NULL)
    printf("Thread_id (main) %lx\n", pthread_self());
  else
	printf("Thread_id %lx\n", pthread_self());
  while (getchar() != '\n'){
    n++;
  }
  printf("exiting %lx\n", pthread_self());
  int* return_value = (int*)malloc(sizeof(int));
  *return_value = n;
  pthread_exit(return_value);
  
}

int main(int argc, char * argv[]){
  int n_threads;
  
  int n;
  if(argc == 1 || sscanf(argv[1], "%d", & n_threads) != 1)
    exit(-1);

  printf("Creating %d Threads\n", n_threads);
  
  pthread_t* thread_ids = (pthread_t*) malloc(n_threads * sizeof(pthread_t));
  int** retvals_ptr = (int**) malloc(n_threads * sizeof(int*));
  for (n= 0; n < n_threads; n++)
  {
    pthread_create(thread_ids + n, NULL, thread_func, NULL);
  }

  for (n = 0; n < n_threads; n++)
  {
    pthread_join(thread_ids[n], retvals_ptr+n);
  }
  
  for (n = 0; n < n_threads; n++)
  {
    printf("Number of characters of %lx: %d \n", thread_ids[n], *retvals_ptr[n]);
  }
  exit(0);


}
