/******************************************************************************
 *
 * File Name: main7.c
 *	      (c) 2010 AED
 * Author:    AED Team
 * Revision:  v2.2 ACR
 *
 * NAME
 *     main7 - Sorting arrays
 *
 * SYNOPSIS
 *		#include <stdlib.h>
 *		#include <stdio.h>
 *		#include <string.h>
 *		#include "word.h"
 *
 * DESCRIPTION
 *
 * DIAGNOSTICS
 *          tested
 *****************************************************************************/

#define ASCENDENTE 1
#define DESCENDENTE 2
#define ALFABETICA 1
#define COMPRIMENTO 2
#define OCORRENCIAS 3

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "word.h"

int main(int argc, char **argv)
{
  int nt_palavras;              /* total number of words in input file */
  int n_palavras;               /* number of distint words in input file */
  t_tabela tabela;              /* table holding the structure */

  /* default initialization for alfabetic order and ascending */
  int criterio = ALFABETICA;
  int sentido  = ASCENDENTE;
  char *ficheiro = argv[1];

  nt_palavras = AllocaTabelaPalavras(&tabela, ficheiro);
  n_palavras = PreencheTabelaPalavras(&tabela, ficheiro);

  argv++;                       /* increments index of argv to point to the
                                   second argument */
  while (*(++argv)) {
    if (strcmp(*argv, "-alfabetica") == 0)
      criterio = ALFABETICA;
    else if (strcmp(*argv, "-ocorrencias") == 0)
      criterio = OCORRENCIAS;
    else if (strcmp(*argv, "-comprimento") == 0)
      criterio = COMPRIMENTO;
    else if (strcmp(*argv, "-a") == 0)
      sentido = ASCENDENTE;
    else if (strcmp(*argv, "-d") == 0)
      sentido = DESCENDENTE;
    else {
      fprintf(stderr, "Wrong arguments\n");
      exit(3);
    }
  }

  if ((criterio == ALFABETICA) && (sentido == ASCENDENTE)) {
    sort((Item*) tabela, 0, n_palavras - 1, lessAlfabetica);
  }
  if ((criterio == ALFABETICA) && (sentido == DESCENDENTE)) {
    sort((Item*) tabela, 0, n_palavras - 1, moreAlfabetica);
  }
  if ((criterio == OCORRENCIAS) && (sentido == ASCENDENTE)) {
    sort((Item*) tabela, 0, n_palavras - 1, lessOcorrencias);
  }
  if ((criterio == OCORRENCIAS) && (sentido == DESCENDENTE)) {
    sort((Item*) tabela, 0, n_palavras - 1, moreOcorrencias);
  }
  if ((criterio == COMPRIMENTO) && (sentido == ASCENDENTE)) {
    sort((Item*) tabela, 0, n_palavras - 1, lessComprimento);
  }
  if ((criterio == COMPRIMENTO) && (sentido == DESCENDENTE)) {
    sort((Item*) tabela, 0, n_palavras - 1, moreComprimento);
  }
  
  EscreveFicheiro(&tabela, ficheiro, n_palavras);
  printf("Number of different words: %d\n", n_palavras);

  /* -- Insert code to call functions to free allocated memory -- */
  LibertaTabelaPalavras(&tabela, n_palavras);

  /* ------------------------------------------------------------ */

  return 0;
}
