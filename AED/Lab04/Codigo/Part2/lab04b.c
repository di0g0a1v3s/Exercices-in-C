/*
 *  File name: lab03b.c
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: See the handout for Lab 03.
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */



/* Header Inclusions                                              */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Entry.h"

#define ASCENDENTE 1
#define DESCENDENTE 2
#define ID 1
#define AGE 2
#define HEIGHT 3
#define WEIGHT 4




/*
 *  Function:
 *    readEntryFile2LinkedList
 *
 *  Description:
 *    Reads the entries from a file and creates a linked list with
 *   these entries in the inverse order.
 *
 *  Arguments:
 *    Pointer to the file stream:
 *        FILE * fp
 *
 *  Return value:
 *    Pointer to the first node of the linked list.
 */
LinkedList * readEntryFile2LinkedList(FILE * fp, int sentido, int criterio)
{
  int id;
  int age;
  int height;
  int weight;
  int err;

  LinkedList * lp;
  Entry * entry;

  /* Initialize linked list                                       */
  lp = initLinkedList();

  /* Cycle through file rows                                      */
  while(fscanf(fp, "%d %d %d %d", &id, &age, &height, &weight) == 4)
  {
    /* Create new entry                                           */
    entry = newEntry(id, age, height, weight);

    /* Store entry in the linked list                             */
	if(sentido == ASCENDENTE && criterio == ID)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpAscendenteId, &err);
	else if(sentido == ASCENDENTE && criterio == AGE)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpAscendenteAge, &err);
	else if(sentido == ASCENDENTE && criterio == HEIGHT)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpAscendenteHeight, &err);
	else if(sentido == ASCENDENTE && criterio == WEIGHT)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpAscendenteWeight, &err);
	else if(sentido == DESCENDENTE && criterio == ID)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpDescendenteId, &err);
	else if(sentido == DESCENDENTE && criterio == AGE)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpDescendenteAge, &err);
	else if(sentido == DESCENDENTE && criterio == HEIGHT)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpDescendenteHeight, &err);
	else if(sentido == DESCENDENTE && criterio == WEIGHT)
       lp = insertSortedLinkedList(lp,(Item) entry, cmpDescendenteWeight, &err);
	  
	if(err != 0) break;
  }

  return lp;
}





/*
 *  Function:
 *    writeEntryFile
 *
 *  Description:
 *    Writes the entries from a linked list to a file.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *      LinkedList * lp
 *    Pointer to the file stream:
 *      FILE * fp
 *
 *  Return value:
 *    None.
 */
void writeEntryFile(LinkedList * lp, FILE *fp)
{
  LinkedList * aux;

  aux = lp;
  while(aux != NULL)
  {
    printEntry((Entry *) getItemLinkedList(aux), fp);
    aux = getNextNodeLinkedList(aux);
  }
}





/*
 *  Function:
 *    freeEntryItem
 *
 *  Description:
 *    Frees the memory allocated to an Item of the type Entry
 *
 *  Arguments:
 *    Pointer to the item
 *      Item item
 *
 *  Return value:
 *    None.
 */
void freeEntryItem(Item item)
{
  freeEntry((Entry *) item);
}





/*
 * Function:
 *   main
 */
int main(int argc, char *argv[])
{
  FILE * fp;
  LinkedList * lp;

  char extOut[] = ".sort";
  char * fileNameIn;
  char * fileNameOut;

/* default initialization for id order and ascending */
  	int criterio = ID;
  	int sentido  = ASCENDENTE;
	
  /* Check number of arguments                                    */
  if(argc < 2)
  {
    printf("Usage: lab03b [filename] [arguments opcions]\n");
    exit(1);
  }
	
	fileNameIn = argv[1];
	
	
	
  argv++;                       /* increments index of argv to point to the
                                   second argument */
  while (*(++argv)) {
    if (strcmp(*argv, "-id") == 0)
      criterio = ID;
    else if (strcmp(*argv, "-age") == 0)
      criterio = AGE;
    else if (strcmp(*argv, "-height") == 0)
      criterio = HEIGHT;
    else if (strcmp(*argv, "-weight") == 0)
      criterio = WEIGHT;
    else if (strcmp(*argv, "-a") == 0)
      sentido = ASCENDENTE;
    else if (strcmp(*argv, "-d") == 0)
      sentido = DESCENDENTE;
    else {
      fprintf(stderr, "Wrong arguments\n");
      exit(3);
    }
  }

  /* Open input file                                              */
  fp  = fopen(fileNameIn, "r");
  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }


  /* Read input file and construct linked list with entries       */
  lp = readEntryFile2LinkedList(fp, sentido, criterio);


  /* Close input file                                             */
  fclose(fp);


  /* Determine output filename                                    */
  fileNameOut = (char *) malloc(sizeof(char) * 
                                 (strlen(fileNameIn) + 
                                  strlen(extOut) + 1));
  if(fileNameOut == NULL)
  {
    printf("Memory allocation error for fileNameOut.\n");
    exit(1);
  }

  strcpy(fileNameOut, fileNameIn);
  strcat(fileNameOut, extOut);


  /* Open output file                                             */
  fp  = fopen(fileNameOut, "w");

  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }


  /* Write entries to output file                                 */
  writeEntryFile(lp, fp);


  /* Free space allocated to fileNameOut                          */
  free(fileNameOut);


  /* Close output file                                            */
  fclose(fp);


  /* Free linked list with entries                                */
  freeLinkedList(lp, freeEntryItem);


  return 0;
}
