/******************************************************************************
 *
 * File Name: main.c
 *	      (c) 2010 AED
 * Authors:    AED Team
 * Last modified: ACR 2010-03-17
 * Revision:  v2.1
 *
 * COMMENTS
 *		Main program
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "words.h"
#include "list.h"
#include "utils.h"


/******************************************************************************
 * Usage ()
 *
 * Arguments: nomeProg - name of executable
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: message function when arguments are missing
 *
 *****************************************************************************/

void Usage(char *nomeProg) {

  printf("Usage: %s [filename] <INICIO>/<FIM>\n",
         nomeProg);
  exit(1);
}


/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int
 * Side-Effects: none
 *
 * Description: main Program
 *
 *****************************************************************************/


int main(int argc, char *argv[]) {
  t_lista *lp;
  int numTotalPalavras = 0;
  int numPalavrasDiferentes;
  int usage = INICIO; 
  char extOut[] = ".palavras";
  char *nomeFicheiroIn, *nomeFicheiroOut;
  FILE *fpIn,*fpOut;

  if(argc > 3 || argc < 2)
    Usage(argv[0]);
	
  if(argc == 3 && strcmp("INICIO", argv[2]) == 0)
	  usage = INICIO;
  else if(argc == 3 && strcmp("FIM", argv[2]) == 0)
	  usage = FIM;
  else if(argc == 3)
	  Usage(argv[0]);

  nomeFicheiroIn = argv[1];
  nomeFicheiroOut = (char*) malloc((strlen(nomeFicheiroIn)+strlen(extOut)+1) * sizeof(char));
  if(nomeFicheiroOut == NULL)
    erroMemoria("Memory allocation for nomeFicheiroOut in main" );

  strcpy(nomeFicheiroOut,nomeFicheiroIn);
  strcat(nomeFicheiroOut,extOut);

  /* open input file */
  fpIn  = fopen(nomeFicheiroIn,"r");
  if(fpIn == NULL) {
    printf("Open error of input file\n");
	exit(2);
  }

  lp = leFicheiro(fpIn,&numTotalPalavras);

  /* open output file */
  fpOut = fopen(nomeFicheiroOut,"w");
  if(fpOut == NULL) {
    printf("Open error of output file\n");
	exit(3);
  }
  if(usage == INICIO)
	escrevePalavrasInicio(lp,fpOut, numTotalPalavras);
  else
	escrevePalavrasFim(lp,fpOut, numTotalPalavras);

  numPalavrasDiferentes = numItensNaLista(lp);
  printf("Number of words = %d, Number of different words = %d\n",
	 numTotalPalavras,numPalavrasDiferentes);

  /* free allocated memory for list of words */
  libertaLista(lp, libertaItem);

  /* -- CLOSE ALL OPENED FILES -- */
  fclose(fpIn);
  fclose(fpOut);

  /* -- ANY OTHER MEMORY YOU HAVE ALLOCATED -- */
  free(nomeFicheiroOut);

  exit(0);
}

