#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "galo-config.h"


int sock_fd;
char play_char;
int gameOver = 0;

void read_play(play *p, char player){
  char linha[100];
  int play_ok=0;

  do{
    printf("please play 0..2 0..2 (%c): ", player);
    fgets(linha, 100, stdin);
    if (sscanf(linha, "%d %d", & p->play[0], &p->play[1]) == 2){
      if(p->play[0]>=0 && p->play[0]<=2&& p->play[1]>=0 && p->play[1]<=2){
        play_ok = 1;
      }
    }
  }while(!play_ok);
}

void* read_play_routine(void* args)
{
  play p;
  while(gameOver != 1)
  {
    read_play(&p, play_char);
    write(sock_fd, &p, sizeof(p));
  }

}



int print_board(board b){
  int i, j;
  printf("\n");
  for(i = 0; i<3; i++){
    printf("|");
    for (j = 0; j < 3; j++)
      printf("%c", b.board[i][j]);
    printf("|\n");
  }
}




void* receive_board_routine(void* args)
{
  board b;
  while(1)
  {
    read(sock_fd, &b, sizeof(b));
    print_board (b);
    if(b.winner != ' ')
    {
      if (b.winner !='E'){
        printf("winner - %c\n", b.winner);
        gameOver = 1;
        break;
      }else{
        printf("No Winner");
        gameOver = 1;
        break;
      }
    }
  }
}


int main(int argc, char * argv[]){
  struct sockaddr_in server_addr;

  if (argc <2){
    printf("second argument should be server address\n");
    exit(-1);
  }
  sock_fd= socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd == -1){
    perror("socket: ");
    exit(-1);
  }
  server_addr.sin_family = AF_INET;
	// this values can be read from the keyboard
	server_addr.sin_port= htons(GALO_PORT);
	inet_aton(argv[1], &server_addr.sin_addr);
  if( -1 == connect(sock_fd,
			(const struct sockaddr *) &server_addr,
			sizeof(server_addr))){
				printf("Error connecting\n");
				exit(-1);
	}
  printf("1 - client connected\n");


  read(sock_fd, &play_char, sizeof(play_char));
  printf("player %c\n", play_char);

  pthread_t read_plays_thread;
  pthread_t receive_board_thread;
  pthread_create(&read_plays_thread, NULL, read_play_routine, NULL);
  pthread_create(&receive_board_thread, NULL, receive_board_routine, NULL);

  int ret;
  pthread_join(receive_board_thread, NULL);
  close(sock_fd);
  printf("-------\n");
  exit(0);
  pthread_join(read_plays_thread, NULL);





}
