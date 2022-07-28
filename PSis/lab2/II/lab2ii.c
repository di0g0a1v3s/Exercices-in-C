#include <sys/types.h>
#include <sys/wait.h>
#include <time.h> 
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{	
	
	for(int i = 0; i < 10; i++)
	{
		pid_t child_pid = fork();
		
		if(child_pid == 0)
		{
			srand(time(NULL) + getpid()); 
			int num_seconds = random()%10 + 1;
			sleep(num_seconds);

			exit(num_seconds);
			
		}	
	}
	
	int sleep_time = 0;
	do
	{
		
		pid_t child_pid = wait(&sleep_time);
		printf("My child was asleep for %d seconds and his PID was %d. My PID is %d\n", WEXITSTATUS(sleep_time), child_pid, getpid());
	
		if(fork() == 0)
		{
			srand(time(NULL) + getpid()); 
			int num_seconds = random()%10 + 1;
			sleep(num_seconds);

			exit(num_seconds);
			
		}	
		
	}while(WIFEXITED(sleep_time));

	return 0;
}