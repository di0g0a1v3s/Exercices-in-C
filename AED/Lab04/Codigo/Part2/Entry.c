/*
 *  File name: Entry.c
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: C-Implementation of functions for type entry
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */


/* Header Inclusions                                              */
#include<stdio.h>
#include<stdlib.h>
#include "defs.h"



/* Include Header File with Data Type and Function Prototypes     */
#include"Entry.h"



/*
 *  Data Type: EntryStruct
 *
 *  Description: Structure with:
 *                 1) Pointer to the item of the linked list node
 *                 2) Pointer to next node of the linked list.
 */
struct EntryStruct
{
  int id;
  int age;
  int height;
  int weight;
};



/*
 *  Function:
 *    newEntry
 *
 *  Description:
 *    Initializes a new entry.
 *
 *  Arguments:
 *    Identification number:
 *      (int) id
 *    Age:
 *     (int) age
 *    Heigth:
 *     (int) Height
 *    Weight:
 *     (int) weight
 *
 *  Return value:
 *    Returns the pointer to the new entry in case of success, NULL
 *   otherwise.
 */
Entry * newEntry(int id, int age, int height, int weight)
{
  Entry * new;

  /* Memory allocation                                            */
  new = (Entry *) malloc(sizeof(Entry));

  /* Check memory allocation errors                               */
  if(new == NULL)
    return NULL;

  /* Fill in entry values                                         */
  new->id = id;
  new->age = age;
  new->height = height;
  new->weight = weight;

  return new;
}



/*
 *  Function:
 *    getIdEntry
 *
 *  Description:
 *    Returns the id of an entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Entry id.
 */
int getIdEntry(Entry * entry)
{
  return entry->id;
}



/*
 *  Function:
 *    getAgeEntry
 *
 *  Description:
 *    Returns the age in the entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Age stored in the entry.
 */
int getAgeEntry(Entry * entry)
{
  return entry->age;
}



/*
 *  Function:
 *    getHeightEntry
 *
 *  Description:
 *    Returns the age in the entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Height stored in the entry.
 */
int getHeightEntry(Entry * entry)
{
  return entry->height;
}



/*
 *  Function:
 *    getWeightEntry
 *
 *  Description:
 *    Returns the age in the entry.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    Weight stored in the entry.
 */
int getWeightEntry(Entry * entry)
{
  return entry->weight;
}



/*
 *  Function:
 *    printEntry
 *
 *  Description:
 *    Prints an entry in a file.
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *    Pointer to stream:
 *      (FILE *) fp;
 *
 *  Return value:
 *    None.
 */
void printEntry(Entry * entry, FILE * fp)
{
  fprintf(fp, "%d %d %d %d\n", 
          entry->id, entry->age, entry->height, entry->weight);
}



/*
 *  Function:
 *    freeEntry
 *
 *  Description:
 *    Frees the memory allocated to an entry
 *
 *  Arguments:
 *    Pointer to entry:
 *      (Entry *) entry
 *
 *  Return value:
 *    None.
 */
void freeEntry(Entry * entry)
{
  free(entry);
}


int cmpAscendenteId(Item a, Item b)
{
	if( ((Entry*)a)->id > ((Entry*)b)->id )
		return 1;
	else 
		return 0;
}
int cmpAscendenteAge(Item a, Item b)
{
	if( ((Entry*)a)->age > ((Entry*)b)->age )
		return 1;
	else 
		return 0;
}
int cmpAscendenteHeight(Item a, Item b)
{
	if( ((Entry*)a)->height > ((Entry*)b)->height )
		return 1;
	else 
		return 0;
}
int cmpAscendenteWeight(Item a, Item b)
{
	if( ((Entry*)a)->weight > ((Entry*)b)->weight )
		return 1;
	else 
		return 0;
}
int cmpDescendenteId(Item a, Item b)
{
	if( ((Entry*)a)->id < ((Entry*)b)->id )
		return 1;
	else 
		return 0;
}
int cmpDescendenteAge(Item a, Item b)
{
	if( ((Entry*)a)->age < ((Entry*)b)->age )
		return 1;
	else 
		return 0;
}
int cmpDescendenteHeight(Item a, Item b)
{
	if( ((Entry*)a)->height < ((Entry*)b)->height )
		return 1;
	else 
		return 0;
}
int cmpDescendenteWeight(Item a, Item b)
{
	if( ((Entry*)a)->weight < ((Entry*)b)->weight )
		return 1;
	else 
		return 0;
}

