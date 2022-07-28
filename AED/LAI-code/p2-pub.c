m#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>



int vec_process(int *veci, int iL, int iR)
{
  int k, res;

  for (res = 0, k = iL; k < iR; k++) {

    if (veci[k] == veci[k + 1]) {
      res++;
    }
  }

  return res;
}


int main(int argc, char *argv[])
{
  int i, j, M, N, result=0, **vec;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s M N\n", argv[0]);
    exit(1);
  }

  /* read numbers MUST be positive  */
  M = atoi(argv[1]);
  N = atoi(argv[2]);
  if (M <= 0 || N <= 0) {
    fprintf(stderr, "Usage: %s M N\n", argv[0]);
    fprintf(stderr, "M and N must be positive\n");
    exit(1);
  }

  /* allocate memory for tables and read data */
  vec = (int**) malloc(M * sizeof(int*));
  if ( vec == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 4 );
  }
  for(i = 0; i < M; i++)
  {
	  vec[i] = (int*) malloc(N * sizeof(int));
	  if ( vec[i] == NULL ) {
		fprintf ( stderr, "ERROR: not enough memory available!\n" );
		exit ( 4 );
	  }
  }
  
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      scanf("%d", &vec[i][j]);

  /* Now process array */
  for (i = 0; i < M; i++) {
    result = vec_process(vec[i], 0, N-1);
    printf("result[vector %d]:  %d \n", i, result);
  }

  /* free memory */
  for(i = 0; i < M; i++)
  {
	  free(vec[i]);
  }
  free(vec);

  exit(0);
}
