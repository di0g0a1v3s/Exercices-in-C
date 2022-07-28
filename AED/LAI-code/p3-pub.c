/******************************************************************************
 *
 * File Name: p3-pub.c
 *	      (c) 2017 AED
 * Author:    Nuno Neves & AED Team
 * Revision:  17 Oct 2017
 *
 * NAME
 *     p3-pub.c - memory management simulator
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "memmgt.h"

int main(void)
{
  int ret, val = 0, done=0;
  char cmd = 0, line[128];


  do {
    (void) fgets(line, 128, stdin);
    sscanf(line, "%c %d", &cmd, &val);

    if(cmd != 'M' || val <= 0) fprintf ( stdout, "-3\n");

  } while (cmd != 'M' || val <= 0);
  /* Espera por comando de inicializacao de memoria */

  startMemoryManager(val);

  /* Ciclo principal */
  while (!done) {

    (void) fgets(line, 128, stdin);
    sscanf(line, "%c %d", &cmd, &val);

    switch (cmd) {

    case 'R':
      /* pedido de alocação */
      if(val < 0) {
        fprintf(stderr, "-3\n");
        break;
      }

      /* Saida do programa com o comando 'R 0' */
      if(val == 0) {
        done = 1;
        break;
      }

      /* Alocacao de memoria */
      ret = myMalloc(val);
      if (ret == -1)
        fprintf ( stdout, "%d\n", ret);
      else
        fprintf ( stdout, "%d %d\n", val, ret);

      break;

    case 'F':
      if(val < 0) {
        fprintf(stderr, "-3\n");
        break;
      }

      /* Libertacao de memoria */
      ret = myFree(val);
      if (ret == -2)
        fprintf ( stdout, "%d\n", ret);
      else
        fprintf ( stdout, "%d %d\n", ret, val);

      break;
	
	case 'S':
	  if(val != 0)
		fprintf(stderr, "-3\n");
	  else
		 showMem();
			
	  break;


    default:
      fprintf(stderr, "-3\n");
    }
  }

  /* Saida do programa com libertacao do gestor de memoria */
  closeMemoryManager();

  return 0;
}
