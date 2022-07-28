#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "galo_consts.h"


void send_board(char board[3][3], int socket, int state)
{
  //send lines one at a time
  int i = 0;
  for(i = 0; i < 3; i++)
  {
    send(socket, board[i], sizeof(char)*3, 0);
  }
  send(socket, &state, sizeof(int), 0);

}

void recv_play(int play[2], int socket)
{
  recv(socket, play, sizeof(int)*2, 0);

}



int clear_board(char board[3][3]){
  int i, j;

  for(i = 0; i<3; i++)
    for (j = 0; j < 3; j++)
      board[i][j]=' ';
}

int ver_win(char board[3][3], char player){
  if((board[0][0]+board[1][0]+board[2][0])/3 == player)
    return 1;
  if((board[0][1]+board[1][1]+board[2][1])/3 == player)
      return 1;
  if((board[0][2]+board[1][2]+board[2][2])/3 == player)
      return 1;
  if((board[0][0]+board[0][1]+board[0][2])/3 == player)
        return 1;
  if((board[1][0]+board[1][1]+board[1][2])/3 == player)
        return 1;
  if((board[2][0]+board[2][1]+board[2][2])/3 == player)
        return 1;
  if((board[0][0]+board[1][1]+board[2][2])/3 == player)
        return 1;
  if((board[0][2]+board[1][1]+board[2][2])/3 == player)
        return 1;
}

int put_play(char board[3][3], int play[2], char player){
  if (  board[play[0]][play[1]] == ' '){
    board[play[0]][play[1]]=player;
    return 1;
  }else{
    return 0;
  }
}

int main(){
  char b[3][3];
  int play[2];

  int sock_player_o;
  int sock_player_x;

  struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t size_client_addr;

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd == -1){
    perror("socket: ");
    exit(-1);
  }

  server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY; //machine address

  int err = bind(sock_fd, (struct sockaddr *)&server_addr,
							sizeof(server_addr));
	if(err == -1) {
		perror("bind");
		exit(-1);
	}
	printf("Socket created and binded \n ");

	listen(sock_fd, 2);

  printf("Waiting for players... \n ");

  int connected_players = 0;
  int sock_accepted = -1;
  while(connected_players < 2)
  {
    sock_accepted = accept(sock_fd, (struct sockaddr *)&client_addr, &size_client_addr);
    if(sock_accepted != -1 && connected_players == 0)
    {
      sock_player_x = sock_accepted;
      connected_players = 1;
      printf("Player 'x' connected. Waiting for player 'o'... \n ");
      char player = 'x';
      send(sock_player_x, &player, sizeof(char), 0);
    }
    else if(sock_accepted != -1 && connected_players == 1)
    {
      sock_player_o = sock_accepted;
      connected_players = 2;
      printf("Player 'o' connected. Starting game... \n ");
      char player = 'x';
      send(sock_player_o, &player, sizeof(char), 0);
    }
  }


  clear_board(b);

  while(1){
    do{
      send_board (b, sock_player_x, NONE);
      recv_play(play, sock_player_x);
    }while (put_play(b, play, 'x') != 1);

    printf("Player 'x' has played...\n");

    if (ver_win(b, 'x') ==1){
      send_board (b, sock_player_x, WIN);
      send_board (b, sock_player_o, LOSS);
      printf("winner - x\n");
      break;
    }

    do{
      send_board (b, sock_player_o, NONE);
      recv_play(play, sock_player_o);
    }while (put_play(b, play, 'o') != 1);

    printf("Player 'o' has played...\n");

    if (ver_win(b, 'o') ==1){
      send_board (b, sock_player_o, WIN);
      send_board (b, sock_player_x, LOSS);
      printf("winner - o\n");
      break;
    }

 }

 close(sock_fd);
 close(sock_player_x);
 close(sock_player_o);
}
