#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "galo_consts.h"

void recv_board(char board[3][3], int socket, int* state)
{
  int i = 0;
  for(i = 0; i < 3; i++)
  {
    recv(socket, board[i], sizeof(char)*3, 0);
  }
  recv(socket, state, sizeof(int), 0);

}

void send_play(int play[2], int socket)
{
  send(socket, play, sizeof(int)*2, 0);

}

int print_board(char board[3][3]){
  int i, j;
  for(i = 0; i<3; i++){
    printf("|");
    for (j = 0; j < 3; j++)
      printf("%c", board[i][j]);
    printf("|\n");
  }
}

void read_play(int play[2], char player){
  char linha[100];
  int play_ok=0;

  do{
    printf("please play 0..2 0..2 (%c): ", player);
    fgets(linha, 100, stdin);
    if (sscanf(linha, "%d %d", &play[0], &play[1]) == 2){
      if(play[0]>=0 && play[0]<=2&& play[1]>=0 && play[1]<=2){
        play_ok = 1;
      }
    }
  }while(!play_ok);
}

int main(){
  char b[3][3];
  int play[2];
  int state = NONE;
  char player;
	struct sockaddr_in server_addr;

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1){
		perror("socket: ");
		exit(-1);
	}
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_aton("127.0.0.1", &server_addr.sin_addr);

  printf("Waiting for server to connect...\n");
  while(connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
  { }
  printf("Connected to server\n");
  recv(sock_fd, &player, sizeof(char), 0);

  while(1)
  {
    recv_board(b, sock_fd, &state);

    if(state == NONE)
    {
      print_board(b);
      read_play(play, player);
      send_play(play, sock_fd);
    }
    else if(state == WIN)
    {
      print_board(b);
      printf("YOU WON!\n");
      break;
    }
    else if(state == LOSS)
    {
      print_board(b);
      printf("You Lost. Better Luck Next Time!\n");
      break;
    }
  }

  close(sock_fd);


}
