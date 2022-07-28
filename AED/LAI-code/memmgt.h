/******************************************************************************
 *
 * File Name: memmgt.h
 *	      (c) 2017 AED
 * Author:    Nuno Neves & AED Team
 * Revision:  17 Oct 2017
 *
 * NAME
 *     memmgt.h - memory management
 *
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#ifndef _MEMMGT_H
#define _MEMMGT_H

#include <stdio.h>
#include <stdlib.h>

void startMemoryManager(int size);
void closeMemoryManager();
int myMalloc(int size);
int myFree(int address);
int showMemory();

#endif
