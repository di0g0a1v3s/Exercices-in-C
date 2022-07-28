/******************************************************************************
 *
 * File Name: tree.h
 *	      (c) 2009 AED
 * Author:    AED team
 * Revision:  v2.2 ACR
 *
 * NAME
 *     tree  - prototypes
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#if !defined(__APPLE__)
#include <malloc.h>
#endif

#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))

typedef enum
{
    FALSE=0,
    TRUE=1
} Boolean;


typedef struct _Node Node;

Node *AllocNode ();
Node *NewNode (int num);
Node *Construct (FILE *fp, char * filename);
void espaco (int n);
void PreFixed (Node *root, int n);
void InFixed (Node *root, int n);
void PosFixed (Node *root, int n);
void sweepDepth (Node *root, int n);
void sweepBreadth (Node *root);
void FreeTree(Node *root);
Boolean isTreeOrdered(Node *root);
Boolean verifyOrder(int value);
Boolean isTreeBalanced(Node *root);
int height(Node *root);
Boolean isTreeOrderedWrong(Node *root);
