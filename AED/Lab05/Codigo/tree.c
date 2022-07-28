/******************************************************************************
 *
 * File Name: tree.c
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 *
 * NAME
 *     Tree - different forms of tree sweep
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <malloc.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS
 *
 *****************************************************************************/

/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
*/
#include <limits.h>
#include "tree.h"
#include "queue.h"

struct _Node {
  int value;
  struct _Node *left, *right;
};

/******************************************************************************
 * AllocNode()
 *
 * Arguments: (none)
 * Returns: new node
 * Side-Effects: none
 *
 * Description: allocates space for a new node
 *
 *****************************************************************************/


Node *AllocNode() {
  return ((Node *) malloc(sizeof(Node)));
}


/******************************************************************************
 * NewNode()
 *
 * Arguments:
 * Returns: new node
 * Side-Effects: none
 *
 * Description: creates a new node
 *
 *****************************************************************************/

Node *NewNode(int num)
{
    Node *aux;
    
    if (num==-1)
        return NULL;
    
    aux = AllocNode();
    aux->value = num;
    aux->right = aux->left = NULL;
    
    return aux;
}

/******************************************************************************
 * Construct()
 *
 * Arguments: n - number of levels
 * Returns: pointer to root node of the tree
 * Side-Effects: none
 *
 * Description: constructs a tree with n levels
 *
 *****************************************************************************/

Node *Construct(FILE *fp, char * filename)
{
    Node *nodeRoot;
    int num;
    
    if (fscanf(fp,"%d", &num) == EOF)
    {
        fprintf(stderr, "File %s has an insufficient number of values.  Please correct.\n", filename);
        exit(0);
    }
    
    if ((nodeRoot = NewNode(num)) != NULL)
    {
        /* links to child */
        nodeRoot->left  = Construct(fp, filename);
        nodeRoot->right = Construct(fp, filename);
    }
    
    return nodeRoot;
}
/******************************************************************************
 * spaces()
 *
 * Arguments: n - number of spaces
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints n spaces
 *
 *****************************************************************************/

void spaces(int n)
{
  int i;

  for (i = 0; i < n; i++)
    printf("  ");
  return;
}


/******************************************************************************
 * PreFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PreFix format
 *
 *****************************************************************************/

void PreFixed(Node *root, int n)
{
  if (root != NULL) {
    spaces(n);
    printf("%d\n", root->value);
    PreFixed(root->left, n + 1);
    PreFixed(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * InFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the InFix format
 *
 *****************************************************************************/

void InFixed(Node *root, int n)
{

  /* Insert code */
  if (root != NULL) {
    InFixed(root->left, n + 1);
    spaces(n);
    printf("%d\n", root->value);
    InFixed(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * PosFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PosFix format
 *
 *****************************************************************************/

void PosFixed(Node *root, int n)
{

  /* Insert code */
  if (root != NULL) {
    PosFixed(root->left, n + 1);
    PosFixed(root->right, n + 1);
    spaces(n);
    printf("%d\n", root->value);
  }

  return;
}


/******************************************************************************
 * sweepDepth()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the depthfirst format
 *
 *****************************************************************************/

void sweepDepth(Node *root, int n)
{

  /* Insert code */
  if (root != NULL) {
    spaces(n);
    printf("%d\n", root->value);
    sweepDepth(root->left, n + 1);
    sweepDepth(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * sweepBreadth()
 *
 * Arguments: root - root of the tree
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the Breathfirst format
 *
 *****************************************************************************/

void sweepBreadth(Node *root)
{
    
    Queue *myq = QueueNew();
    Element *elem;
    
    if (root == NULL) return;
    
    InsertLast(myq, root, 0);
    
    while ((elem=GetFirst(myq)) != NULL) {
        spaces(elem->level);
        printf("%d\n", elem->node->value);
        if (elem->node->left != NULL)
            InsertLast(myq, elem->node->left, elem->level + 1);
        if (elem->node->right != NULL)
            InsertLast(myq, elem->node->right, elem->level + 1);
	
        free(elem);
    }
    free(myq);
    return;
}

/******************************************************************************
 * QueueNew()
 *
 * Arguments: 
 *
 * Returns: a pointer to Queue
 * Side-Effects: none
 *
 * Description: creates an empty queue
 *
 *****************************************************************************/

Queue *QueueNew()
{
  Queue * q = malloc(sizeof(Queue));
  q->first = NULL;
  q->last = NULL;
  return q;
}

/******************************************************************************
 * InsertLast()
 *
 * Arguments: queue - a queue
 *            node - a node to insert last in the queue
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the Breathfirst format
 *
 *****************************************************************************/

void InsertLast(Queue* queue, Node* node, int n)
{
  Element *elem = malloc(sizeof(Element));
  elem->node = node;
  elem->level = n;
  elem->next = NULL;
  if (queue->last != NULL)
     queue->last->next = elem;
  queue->last = elem;
  if (queue->first == NULL)
     queue->first = elem;
}

/******************************************************************************
 * GetFirst()
 *
 * Arguments: queue - a queue
 *            node - a node to insert last in the queue
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the Breathfirst format
 *
 *****************************************************************************/

Element * GetFirst(Queue* queue)
{
  Element * q = queue->first;

  if (queue->first != NULL)
     queue->first = queue->first->next;

  return q;
}


/******************************************************************************
 * FreeTree()
 *
 * Arguments: node - a tree root
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: frees the tree
 *
 *****************************************************************************/

void FreeTree(Node * root)
{
    if (root != NULL) {
	
        FreeTree(root->left);
        FreeTree(root->right);
        free(root);
    }
}

/******************************************************************************
 * IsTreeOrdered()
 *
 * Arguments: node - a tree root
 *            
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is ordered, using the in-fixed sweep
 *
 *****************************************************************************/

Boolean isTreeOrdered(Node * root) {
    /* Insert code */

    if (root != NULL) {
        if (isTreeOrdered(root->left) == FALSE) return FALSE;
        if (verifyOrder(root->value)== FALSE) return FALSE;
        if (isTreeOrdered(root->right) == FALSE) return FALSE;
    }
    
    return TRUE;
}

/******************************************************************************
 * verifyOrder()
 *
 * Arguments: value - a node value
 *
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is ordered, using a static variable to save the previous value
 *
 *****************************************************************************/

Boolean verifyOrder(int value) {
    static int number = INT_MIN;
        
    if (number == INT_MIN)
        number = value;
    else if (number > value)
        return FALSE;
    else
        number = value;
    
    return TRUE;
}

/******************************************************************************
 * IsTreeBalanced()
 *
 * Arguments: node - a tree root
 *
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is AVL balanced
 *
 *****************************************************************************/

Boolean isTreeBalanced(Node * root) {
    if (root == NULL)
        return TRUE;

    if (abs(height(root->right) - height(root->left)) > 1)
        return FALSE;
    
    return isTreeBalanced(root->right) && isTreeBalanced(root->left);
}

/******************************************************************************
 * height()
 *
 * Arguments: node - a tree root
 *
 *
 * Returns: int
 * Side-Effects: none
 *
 * Description: returns the height of a tree
 *
 *****************************************************************************/

int height(Node * root) {
    if (root == NULL)
        return 0;

    return MAX(height(root->right), height(root->left)) + 1;
}

/******************************************************************************
 * IsTreeOrderedWrong()
 *
 * Arguments: node - a tree root
 *
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is (wrong) ordered, by just comparing
 * the parent with the offsprings (if exists)
 *
 *****************************************************************************/

Boolean isTreeOrderedWrong(Node * root) {
    if (root == NULL)
        return TRUE;
    
    if (root->left != NULL)
        if (root->value < root->left->value)
            return FALSE;
    
    if (root->right != NULL)
        if (root->value > root->right->value)
            return FALSE;
    
    return isTreeOrderedWrong(root->left) && isTreeOrderedWrong(root->right);
}


