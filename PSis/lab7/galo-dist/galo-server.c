#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "galo-config.h"

const char players[2]={'X', 'O'};
int players_fd[2];
board b;
pthread_mutex_t mutex[9];

int ver_win(board *b, char player){
  if(b->n_plays == 9)
    b->winner = 'E';
  if((b->board[0][0]+b->board[1][0]+b->board[2][0]) == player*3)
    b->winner = player;
  if((b->board[0][1]+b->board[1][1]+b->board[2][1]) == player*3)
  b->winner = player;
  if((b->board[0][2]+b->board[1][2]+b->board[2][2]) == player*3)
  b->winner = player;
  if((b->board[0][0]+b->board[0][1]+b->board[0][2]) == player*3)
  b->winner = player;
  if((b->board[1][0]+b->board[1][1]+b->board[1][2]) == player*3)
  b->winner = player;
  if((b->board[2][0]+b->board[2][1]+b->board[2][2]) == player*3)
  b->winner = player;
  if((b->board[0][0]+b->board[1][1]+b->board[2][2]) == player*3)
  b->winner = player;
  if((b->board[0][2]+b->board[1][1]+b->board[2][0]) == player*3)
  b->winner = player;

}

int put_play(board *b, play p, char player){
  int x = p.play[0];
  int y = p.play[1];

  pthread_mutex_lock(&(mutex[x+y*2]));
  if (  b->board[x][y] == ' '){
    b->board[x][y]=player;
    b->n_plays ++;
    pthread_mutex_unlock(&(mutex[x+y*2]));
    return 1;
  }else{
    pthread_mutex_unlock(&(mutex[x+y*2]));
    return 0;
  }
}

int play_remote(board * b, char player, int this_player){
  play p;
  int ret = read(this_player, &p, sizeof(p));
  if(ret > 0)
  {
    put_play(b, p, player);
    ver_win(b, player);
  }
  return ret;

}


void* handle_player_routine(void *args)
{
  int player_number = (int) args;
  while(b.winner == ' '){
    if(play_remote(&b, players[player_number], players_fd[player_number]) > 0)
    {
      write(players_fd[0], &b, sizeof(b));
      write(players_fd[1], &b, sizeof(b));
      printf("2 - sent board\n");
    }

  }
}

int clear_board(board *b){
  int i, j;

  for(i = 0; i<3; i++)
    for (j = 0; j < 3; j++)
      b->board[i][j]=' ';
    b->winner = ' ';
    b-> n_plays = 0;
}





int main(){
  struct sockaddr_in local_addr;
  int i;

  for(i = 0; i < 9; i++)
    pthread_mutex_init(&(mutex[i]), NULL);

  int sock_fd= socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1){
    perror("socket: ");
    exit(-1);
  }
  local_addr.sin_family = AF_INET;
  local_addr.sin_port= htons(GALO_PORT);
  local_addr.sin_addr.s_addr= INADDR_ANY;
  int err = bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
  if(err == -1) {
    perror("bind");
    exit(-1);
  }
  printf(" socket created and binded \n");
  listen(sock_fd, 5);
  while(1){
    printf("Waiting for players\n");
    players_fd[0]= accept(sock_fd, NULL, NULL);
    printf("1 - client connected\n");
    players_fd[1]= accept(sock_fd, NULL, NULL);
    printf("1 - client connected\n");

    write(players_fd[0], &players[0], sizeof(players[0]));
    write(players_fd[1], &players[1], sizeof(players[1]));



    clear_board(&b);


    pthread_t players_threads[2];
    for(i = 0; i < 2; i++)
      pthread_create(&(players_threads[i]), NULL, handle_player_routine, (void*) i);

    int ret;
    for(int i = 0; i < 2; i++)
      pthread_join(players_threads[i], NULL);

    for(i = 0; i < 9; i++)
      pthread_mutex_destroy(&(mutex[i]));

    close(players_fd[0]);
    close(players_fd[1]);
    printf("GAME OVER!\n");
  }
  close(sock_fd);
}
