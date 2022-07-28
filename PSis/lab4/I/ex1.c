#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1

int isPrime(int num)
{
	if (num <= 1) return 0;
    if (num % 2 == 0 && num > 2) return 0;
    for(int i = 3; i < num / 2; i+= 2)
    {
    	if (num % i == 0)
        	return 0;
    }
    return 1;
}

int main(int argc, const char* argv[])
{

	int number_of_slaves = 0;
	int number_random_numbers = 0;
	int i = 0;
	int** fd_array;

	srand(time(NULL));

	if(argc < 3)
	{
		printf("Wrong number of arguments\n");
		return 1;
	}
	if(sscanf(argv[1], "%d", &number_of_slaves) != 1)
	{
		printf("Failed to read 1st argument\n");
		return 1;
	}

	if(sscanf(argv[2], "%d", &number_random_numbers) != 1)
	{
		printf("Failed to read 2nd argument\n");
		return 1;
	}

	//n pipes
	fd_array = (int**) malloc(number_of_slaves * sizeof(int*));


	for(i = 0; i < number_of_slaves; i++)
	{
		fd_array[i] = (int*) malloc(sizeof(int)*2);
		if (pipe(fd_array[i]) == -1)
	  {
	        printf("Failed to create pipe\n");
			return 1;
		}
	}


	for(i = 0; i < number_of_slaves; i++)
	{
		//slave
		if(fork() == 0)
		{
			//close unused pipes
			for(int j = 0; j < number_of_slaves; j++)
			{
				if(j != i)
				{
					close(fd_array[j][READ]);
					close(fd_array[j][WRITE]);
				}
			}
			close(fd_array[i][WRITE]);  // Close writing end of pipe

			int number_read;
			int number_of_primes = 0;
			while( read(fd_array[i][READ], &number_read, sizeof(int)) != 0 ) //read from pipe
			{
				if(isPrime(number_read))
					number_of_primes++;
			}
			printf("Number of primes read by process %d: %d\n", getpid(), number_of_primes);
			exit(0);
		}

	}

	//master
	for(int i = 0; i < number_of_slaves; i++)
	{
			close(fd_array[i][READ]);  // Close reading end of pipes
	}

	for(i = 0; i < number_random_numbers; i++)
	{
		int random_number = random()%100000;

		write( fd_array[i%number_of_slaves][WRITE], &random_number, sizeof(int));

	}

	for(int i = 0; i < number_of_slaves; i++)
	{
			close(fd_array[i][WRITE]);  // Close writing end of pipes
	}

	while(wait(NULL) > 0){}

	for(i = 0; i < number_of_slaves; i++)
	{
		free(fd_array[i]);
	}
	free(fd_array);

	exit(0);

}
