#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "sock_dg.h"

#define MAX_STR 1000


int sock_fd;

/*(EX 3) routine that receives reply from server*/
void * replies_thread_routine(void * arg)
{
	char buffer[MAX_STR];
	char server_name[MAX_STR];
	int nbytes;
	int number_received;
	pid_t server_pid;
	int isPrime;
	return_info info;
	while(1)
	{

		nbytes = recv(sock_fd, &info, sizeof(info), 0);
		nbytes += recv(sock_fd, server_name, MAX_STR, 0);
		if(info.isPrime)
		{
			printf("Number is prime, ");
		}
		else
			printf("Number is not prime, ");
		printf("server pid: %d, server name: %s, bytes receives: %d\n", info.server_pid, server_name, nbytes);
	}
}

int main(){
	struct sockaddr_un server_addr;
	struct sockaddr_un local_addr;
	int nbytes;
	int n = 0;
	char linha[MAX_STR];
	int error;
	char sock_address[MAX_STR];
	char buffer[MAX_STR];

	/*(EX 1) Attribute different name to each socket created*/
	strcpy(sock_address, "./socket");
	sprintf(buffer, "%d", getpid());
	strcat(sock_address, buffer);

	srand(time(NULL));
	sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);

	if (sock_fd == -1){
		perror("socket: ");
		exit(-1);
	}



	local_addr.sun_family = AF_UNIX;
	strcpy(local_addr.sun_path, sock_address);
	// exercise 2: comment the following line
	/*(EX 2) if bind isn't executed, the server is unable to send back messages
	to the client because there is no address associated to the client socket*/
  error = bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));

	if(error == -1) {
		perror("bind");
		exit(-1);
	}


	printf(" socket created \n Ready to send\n");

	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, SOCK_ADDRESS);
	pthread_t replies_thread;
	/*(EX 3) thread checks for reply*/
	pthread_create(&replies_thread, NULL,
											replies_thread_routine, NULL);
	while(n >= 0)
	{
		n = random()%10000;
		nbytes = sendto(sock_fd, &n, sizeof(n), 0,
	                    (const struct sockaddr *) &server_addr,
											sizeof(server_addr));
		printf("sent number %d nbytes %d\n", n, nbytes);
		sleep(1);
	}


	close(sock_fd);
	unlink(sock_address);
	exit(0);

}
