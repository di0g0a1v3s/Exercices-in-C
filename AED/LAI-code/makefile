#
#  File name: makefile
#
#  Author: 2013 Fall Semester AED Team
#
#  Release date: 2013/11/02
#
#  Description: Makefile for the individual evaluation laboratory
#
#  Usage:
#     1) To generate the executable file for the program p2-pub, run
#         $ make p2
#
#        To generate the executable file for the program p3-pub, run
#         $ make p3
#
#     2) To clean all object files and the executable file, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic

#  Sources
SOURCES2 =  p2-pub.c
SOURCES3 =  memmgt.c p3-pub.c

#  Objects
OBJECTS2 = p2-pub.o
OBJECTS3 = memmgt.o p3-pub.o

p2:	p2-pub
p2-pub: $(OBJECTS2)
	gcc -g -o $@ $(OBJECTS2)

p3:	p3-pub
p3-pub: $(OBJECTS3)
	gcc -g -o $@ $(OBJECTS3)

memmgt.o: memmgt.h memmgt.c

clean::
	rm -f *.o core a.out p3-pub p2-pub *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
