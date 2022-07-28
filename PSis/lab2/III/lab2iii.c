#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h> 
/* number of times the handle will run: */
int counter = 0;

void handle(int sig) {
    printf("RESET\n");
	counter = 0;
    alarm(random()%10 + 1);
}

int main() {
	srand(time(NULL)); 
    signal(SIGALRM, handle);
    alarm(random()%10 + 1);
    while(1) { 
		counter++;
		printf("%d \n", counter);
		sleep(1);
	}
    return 0;
}