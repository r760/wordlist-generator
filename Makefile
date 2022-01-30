# Makefile for wgen
#
# usage: make wgen
# usage: make clean

CC=gcc
CFLAGS=-Wall -g

clean:
	rm -rf wgen

wgen:	wgen.c
	$(CC) $(CFLAGS) wgen.c -o wgen
