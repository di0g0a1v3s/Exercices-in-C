#include <sys/types.h>
#include<time.h> 
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
			srand(getpid() + time(NULL)); 
			int num_seconds = random()%10 + 1;
			sleep(num_seconds);
			printf("I was asleep for %d seconds and my PID is %d\n", num_seconds, getpid());
			break;
		}
	}

	return 0;
}