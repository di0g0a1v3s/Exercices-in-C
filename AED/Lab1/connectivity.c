/******************************************************************************
 * (c) 2010 AED
 * File Name: connectivity.c
 * Author:    AED Team
 * Last modified: PFF 2010-03-12
 * Revision:  v20100312
 *
 * NAME
 *      connectivity - algorithms for solving the connectivity problem
 *
 * DESCRIPTION
 *      QF QU WQU CWQU, counts number of entry pairs and the number of links
 *      for each method.
 *
 * COMMENTS
 *
 *****************************************************************************/

#include<stdio.h>
#include<stdlib.h>

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *
 *****************************************************************************/
void quick_find(int *id, int N, FILE * fp)
{
  int i, p, q, t;
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  long int search_cnt = 0;           //numero de operações elementares associadas à procura
  long int union_cnt = 0;            //numero de operações elementares associadas à união

  /* initialize; all disconnected */
  for (i = 0; i < N; i++)
    id[i] = i;

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;
    /* do search first */
    search_cnt+=2; //2 leituras
    if (id[p] == id[q]) {
      /* already in the same set; discard */
      printf("\t%d %d\n", p, q);
      continue;
    }

    /* pair has new info; must perform union */
    union_cnt++; //1 leitura
    for (t = id[p], i = 0; i < N; i++)
    {
      union_cnt++; //1 leitura
      if (id[i] == t)
      {
        union_cnt+=2; //1 leitura e 1 escrita
        id[i] = id[q];
      }
    }
    links_cnt++;
    printf(" %d %d\n", p, q);
  }
  printf("QF: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("QF: Operações elementares associadas à:\nProcura: %ld\nUnião: %ld\n", search_cnt, union_cnt);
  
  //IMPRIMIR CONJUNTOS
  printf("\nCONJUNTOS:\n");
  int num_of_sets = 0;
  int cur_id = 0;
  int j = 0;
  for(i = 0; i < N; i++)
  {
    if(id[i] != -1)
    {
      cur_id = id[i];
      num_of_sets++;
    }
    else
      continue;
    
    printf("%d",i);
    for(j = i+1; j < N; j++)
    {
      
      
      if(id[j] == cur_id)
      {
        printf("-%d",j);
        id[j] = -1;
        
      }
        
    }
    printf("\n");
  }
  printf("Numero de conjuntos: %d\n", num_of_sets);
  
}


/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *
 *****************************************************************************/
void quick_union(int *id, int N, FILE * fp)
{

  int i, j, p, q;
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  long long int search_cnt = 0;           //numero de operações elementares associadas à procura
  long long int union_cnt = 0;            //numero de operações elementares associadas à união

  /* initialize; all disconnected */
  for (i = 0; i < N; i++)
    id[i] = i;

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;
    i = p;
    j = q;

    /* do search first */
    
    while (i != id[i])
    {
      i = id[i];
      search_cnt+=2; //2 leituras
      
    }
    search_cnt++; //1 leitura (ultima do while)
    
    while (j != id[j])
    {
      j = id[j];
      search_cnt+=2; //2 leituras
    }
    search_cnt++; //1 leitura (ultima do while)
      

    if (i == j) {
      /* already in the same set; discard */
      printf("\t%d %d\n", p, q);
      continue;
    }

    /* pair has new info; must perform union */
    id[i] = j;
    union_cnt++; //1 escrita
    links_cnt++;

    printf(" %d %d\n", p, q);
  }
  printf("QU: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("QU: Operações elementares associadas à:\nProcura: %lld\nUnião: %lld\n", search_cnt, union_cnt);
}


/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *
 *****************************************************************************/
void weighted_quick_union(int *id, int N, FILE * fp)
{

  int i, j, p, q;
  int *sz = (int *) malloc(N * sizeof(int));
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  long int search_cnt = 0;           //numero de operações elementares associadas à procura
  long int union_cnt = 0;            //numero de operações elementares associadas à união

  /* initialize; all disconnected */
  for (i = 0; i < N; i++) {
    id[i] = i;
    sz[i] = 1;
  }

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;

    /* do search first */
    for (i = p; i != id[i]; i = id[i]) search_cnt+=2;//2 leituras
    search_cnt++; //1 leitura (ultima do for)
    
    for (j = q; j != id[j]; j = id[j]) search_cnt+=2;//2 leituras
    search_cnt++; //1 leitura (ultima do for)

    if (i == j) {
      /* already in the same set; discard */
      printf("\t%d %d\n", p, q);
      continue;
    }

    /* pair has new info; must perform union; pick right direction */
    union_cnt+=2; //2 leituras
    if (sz[i] < sz[j]) {
      id[i] = j;
      union_cnt++; //1 escrita
      sz[j] += sz[i];
      union_cnt += 3; //2 leituras e 1 escrita
    }
    else {
      id[j] = i;
      union_cnt++; //1 escrita
      
      sz[i] += sz[j];
      union_cnt += 3; //2 leituras e 1 escrita
    }
    links_cnt++;

    printf(" %d %d\n", p, q);
  }
  printf("WQU: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("WQU: Operações elementares associadas à:\nProcura: %ld\nUnião: %ld\n", search_cnt, union_cnt);
}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *
 *****************************************************************************/
void compressed_weighted_quick_union(int *id, int N, FILE * fp)
{

  int i, j, p, q, t, x;
  int *sz = (int *) malloc(N * sizeof(int));
  int pairs_cnt = 0;            /* connection pairs counter */
  int links_cnt = 0;            /* number of links counter */
  long int search_cnt = 0;           //numero de operações elementares associadas à procura
  long int union_cnt = 0;            //numero de operações elementares associadas à união

  /* initialize; all disconnected */
  for (i = 0; i < N; i++) {
    id[i] = i;
    sz[i] = 1;
  }

  /* read while there is data */
  while (fscanf(fp, "%d %d", &p, &q) == 2) {
    pairs_cnt++;

    /* do search first */
    for (i = p; i != id[i]; i = id[i]) search_cnt+=2;//2 leituras
    search_cnt++; //1 leitura (ultima do for)
    
    for (j = q; j != id[j]; j = id[j]) search_cnt+=2;//2 leituras
    search_cnt++; //1 leitura (ultima do for)

    if (i == j) {
      /* already in the same set; discard */
      printf("\t%d %d\n", p, q);
      continue;
    }

    /* pair has new info; must perform union; pick right direction */
    union_cnt+=2; //2 leituras
    if (sz[i] < sz[j]) {
      id[i] = j;
      union_cnt++; //1 escrita
      
      sz[j] += sz[i];
      union_cnt += 3; //2 leituras e 1 escrita
      t = j;
    }
    else {
      id[j] = i;
      union_cnt++; //1 escrita
      
      sz[i] += sz[j];
      union_cnt += 3; //2 leituras e 1 escrita
      t = i;
    }
    links_cnt++;

    /* retrace the path and compress to the top */
    for (i = p; i != id[i]; i = x) {
      union_cnt++; //1 leitura
      x = id[i];
      union_cnt++; //1 leitura
      id[i] = t;
      union_cnt++; //1 escrita
    }
    union_cnt++; //1 leitura (ultima do for)
    
    for (j = q; j != id[j]; j = x) {
      union_cnt++; //1 leitura
      x = id[j];
      union_cnt++; //1 leitura
      id[j] = t;
      union_cnt++; //1 escrita
    }
    union_cnt++; //1 leitura (ultima do for)
    printf(" %d %d\n", p, q);
  }
  printf("CWQU: The number of links performed is %d for %d input pairs.\n",
         links_cnt, pairs_cnt);
  printf("WQU: Operações elementares associadas à:\nProcura: %ld\nUnião: %ld\n", search_cnt, union_cnt);
}
