/******************************************************************************
 *
 * File Name: memmgt.c
 *	      (c) 2017 AED
 * Author:    Nuno Neves & AED Team
 * Revision:  17 Oct 2017
 *
 * NAME
 *     memmgt.h - memory management
 *
 * SYNOPSIS
 *     #include "memmgt.h"
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "memmgt.h"

/* possible states of memory blocks */
typedef enum {ALLOC, FREE} mem_state;

/* define basic element of memory management Linked list  */
typedef struct _t_memory {
    int address;
    int size;
    mem_state state;
    struct _t_memory *next;
} t_memory;

/* head of memory management Linked list */
t_memory* memoryLst = NULL;


/******************************************************************************
 * newMemoryBlock()
 *
 * Arguments: address (int)  - address where the block was allocated
 *            size (int)     - size of block
 *            mem_state      - state of the memory block, allocated or free
 * Returns: pointer to newly allocated block
 * Side-Effects: one more block gets allocated
 *               no effects on existing data structures
 *
 * Description: Function for allocating a new memory block
 *
 *****************************************************************************/

t_memory* newMemoryBlock(int address, int size, mem_state state) {

  t_memory* block;

  block = (t_memory*) malloc ( sizeof(t_memory) ); /* COMPLETAR: codigo de alocacao de memoria */

  if( block == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 4 );
  } /* COMPLETAR: verificar alocacao */

  block->address = address; /* COMPLETAR: inicializar campos da estrutura alocada */
  block->size = size;
  block->state = state;
  block->next = NULL;

  return block;
}


/******************************************************************************
 * startMemoryManager()
 *
 * Arguments: size (int)     - size of total memory
 * Returns: (none)
 * Side-Effects: memory management list gets initialized with total memory
 *
 * Description: Function for initializing the memory management system by
 *                allocating a memory block representing the full memory
 *                available
 *
 *****************************************************************************/

void startMemoryManager(int size) {

  memoryLst = newMemoryBlock(0, size, FREE);

  return;
}


/******************************************************************************
 * closeMemoryManager()
 *
 * Arguments: (none)
 * Returns: (none)
 * Side-Effects: clear all info in memory management list and frees all memory
 *
 * Description: Function for clearing all data in the memory management system
 *                and freeing all memory used by the system itself
 *                (not to be confused by the action of freeing the blocks
 *                marked as allocated in the system)
 *
 *****************************************************************************/

void closeMemoryManager() {

  /* COMPLETAR: codigo para libertacao da lista de blocos*/
  t_memory* aux = NULL;
  t_memory* curr = memoryLst;
  while(curr->next != NULL)
  {
	aux = curr->next;
	free(curr);
	curr = aux;
  }
  free(curr);
  memoryLst = NULL;

  return;
}


/******************************************************************************
 * myMalloc()
 *
 * Arguments: size  (int)  - size of requested memory block
 * Returns: address where block was allocated in the existing memory
 * Side-Effects: if the function is successfull, a new block is allocated
 *               and the memory management list is changed accordingly
 * Description: memory allocation algorithm
 *
 *****************************************************************************/

int myMalloc(int size) {

  int address = -1;  /* default is the allocation was not successfull */

  /* COMPLETAR: implementacao do algoritmo
   * de alocacao de memoria pedido no enunciado
   * valor de address é alterado
   FIRST FIT*/
   t_memory* aux = NULL;
   t_memory* curr = memoryLst;
   while(curr != NULL)
   {
	 if(curr->size >= size && curr->state == FREE)
	 {
	   if(curr->size > size)
	   {
		 aux = newMemoryBlock(curr->address + size, curr->size - size, FREE);
		 aux->next = curr->next;
		 curr->next = aux;
	   }
	   address = curr->address;
	   curr->size = size;
	   curr->state = ALLOC;
	   break;	 
	 }
	 curr = curr->next;
   }

  return address;
}

/******************************************************************************
 * mergeAdjacentBlocks()
 *
 * Arguments: block (t_memory*)  - pointer to the first block
 * Returns: size of merged block if merge happened
 * Side-Effects: merges "block" with the block following it in the list, if they're both free,
 *				 creating one single block with size equal to the sum of the previous sizes 
 * Description: merges two adjacent free blocks in the list
 *
 *****************************************************************************/
void mergeAdjacentBlocks(t_memory* block, int* size)
{
  t_memory* aux = NULL;
  if(block != NULL && block->next != NULL && block->next->state == FREE && block->state == FREE)
  {
	 block->size = block->size + block->next->size;
     aux = block->next;
     block->next = block->next->next;
     free(aux);
	 (*size) = block->size;
  }
  
}

/******************************************************************************
 * myFree()
 *
 * Arguments: address (int)  - address where the block was allocated
 * Returns: size of block that was just freed
 * Side-Effects: if the function is successfull, a block previously
 *               allocated in address is now returned; the block may be merged
 *               with the block before it and after it, therefore the list
 *               could be changed
 * Description: memory allocation algorithm
 *
 *****************************************************************************/

int myFree(int address) {

  int size;
  t_memory* find;
  t_memory* aux;

  find = memoryLst;

  /* Procura um bloco alocado no endereco 'address' */
  while(find != NULL) {

    if (find->address == address && find->state == ALLOC) break;

    find = find -> next;
  }

  /* Retorna erro se nao encontrar*/
  if (find == NULL) return -2;

  /* Liberta bloco se encontrar */
  find->state = FREE;
  size = find->size;

  /* COMPLETAR: adicionar codigo para fundir blocos
   * livres adjacentes ao libertado
   */
  
  /*bloco seguinte*/
  mergeAdjacentBlocks(find, &size);
  /*bloco anterior*/
  
  aux = memoryLst;
  while(aux != NULL)
  {
	if(aux->next == find) break;
	aux = aux->next;
  }
  mergeAdjacentBlocks(aux, &size); 
  

  return size;
}




/******************************************************************************
 * showMem()
 *
 * Arguments: (none)
 * Returns: (none)
 * Side-Effects: (none)
 * Description: shows the status of all memory blocks, allocated and free
 *
 *****************************************************************************/

void showMem() {

  t_memory* find;

  find = memoryLst;

  /* COMPLETAR: percorre lista e mostra estado de todos os blocos */
  fprintf(stdout, "Endreço | Dimensão | Estado\n");
  while(find != NULL)
  {
	  fprintf(stdout, "   %d    |    %d     |   %c\n", find->address, find->size, (find->state==FREE) ? 'F' : 'A');
	  find = find->next;
  }

}
