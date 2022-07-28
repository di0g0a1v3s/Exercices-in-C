#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h> 
#include <sys/wait.h>
#define NUMBERS 10000

int isMultipleOf(int num, int of)
{
	if(num%of == 0)
		return 1;
	return 0;
}


int main()
{
	srand(time(NULL));
	int i = 0;
	int numbers[NUMBERS];
	int j = 0;
	for(i = 0; i < NUMBERS; i++)
	{
		int r = rand()%1000 + 1;
		numbers[i] = r;
		
	}
	
	for(int j = 0; j < 4; j++)
	{
		pid_t child_pid = fork();
		
		if(child_pid == 0 && j == 0)
		{
			for(i = 0; i < NUMBERS; i++)
			{
				if(isMultipleOf(numbers[i], 2))
					printf("%d is multiple of 2\n", numbers[i]);
			}
			exit(0);
		}
		
	    if(child_pid == 0 && j == 1)
		{
			for(i = 0; i < NUMBERS; i++)
			{
				if(isMultipleOf(numbers[i], 3))
					printf("%d is multiple of 3\n", numbers[i]);
			}
			exit(0);
		}
														  
	    if(child_pid == 0 && j == 2)
		{
			for(i = 0; i < NUMBERS; i++)
			{
				if(isMultipleOf(numbers[i], 5))
					printf("%d is multiple of 5\n", numbers[i]);
			}
			exit(0);
		}
														  
	    if(child_pid == 0 && j == 3)
		{
			for(i = 0; i < NUMBERS; i++)
			{
				if(isMultipleOf(numbers[i], 7))
					printf("%d is multiple of 7\n", numbers[i]);
			}
			exit(0);
		}
	}
	
	int status = 0;
	pid_t dead;
	while((dead = wait(&status)) != -1)
	{
	}
	
	printf("\n\n");

}

