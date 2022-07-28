#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>

#include "sock_dg.h"

int isPrime(int num)
{
	if (num <= 1)
		return 0;
  if (num % 2 == 0 && num > 2)
		return 0;
  for(int i = 3; i < num / 2; i+= 2)
  {
  	if (num % i == 0)
      	return 0;
  }
  return 1;
}
char* program_name;
void * handle_client_thread_routine(void * arg)
{
	int sock_fd = (int) arg;
	printf("NEW THREAD\n");
	int n;
	int nbytes;
	while(1){
		//recv from need the size of the address !!!

		nbytes = recv(sock_fd, &n, sizeof(n), 0);
		printf("received the number %d in socket %d\n", n, sock_fd);
		return_info info;
		info.isPrime = isPrime(n);
		info.server_pid = getpid();
		pid_t pid = getpid();
		nbytes = send(sock_fd, &info, sizeof(info), 0);
		nbytes+=send(sock_fd, program_name, strlen(program_name) + 1, 0);


		printf("sent %d bytes\n", nbytes);

	}
	close(sock_fd);
}




int main(int agrc, char* argv[]){
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t size_client_addr;

	int sock_fd_accepted;

	program_name = argv[0];

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd == -1){
		perror("socket: ");
		exit(-1);
	}


	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	int err = bind(sock_fd, (struct sockaddr *)&server_addr,
							sizeof(server_addr));
	if(err == -1) {
		perror("bind");
		exit(-1);
	}
	printf(" socket created and binded \n ");

	listen(sock_fd, 10);

	pthread_t thread;
	while(1)
	{
		sock_fd_accepted = accept(sock_fd, (struct sockaddr *)&client_addr, &size_client_addr);

		pthread_create(&thread, NULL,
												handle_client_thread_routine, (void*)sock_fd_accepted);

	}


	close(sock_fd);
	//unlink(SOCK_ADDRESS);
	exit(0);
}
