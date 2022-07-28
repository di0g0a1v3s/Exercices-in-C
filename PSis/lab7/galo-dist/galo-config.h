#define GALO_PORT 3000

typedef struct play{
	int play[2];
}play;

typedef struct board {
  char board[3][3];
  char winner;
  int n_plays;
}board;
