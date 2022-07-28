#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <time.h>
#include <pthread.h>
#include <unistd.h>


void *thread_func (void* arg){
  int n = 0;
  int value = *(int*) arg;
  printf("%d\n", value);
  while (n < value){
    printf("Thread_id %lx - %d \n", pthread_self(), n);
    sleep(1);
    n++;
  }
  printf("exiting %lx \n", pthread_self());
}

int main(int argc, char * argv[]){
  int n_threads;
  pthread_t thread_id;
  int n;
  if(argc ==1 || sscanf(argv[1], "%d", & n_threads) != 1)
    exit(-1);

  printf("Creating %d Threads\n", n_threads);

  int* values = (int*) malloc(n_threads*sizeof(int));
  for (n = 0; n < n_threads; n++)
  {
	  srand(time(NULL)*(n+1));
	  values[n] = rand()%20 + 1;
	  pthread_create(&thread_id, NULL, thread_func, values + n);
  }
    

  getchar();

  exit(0);


}
