# makefile for wordlist-generator
#
# usage: make wordlistGenerator
# usage: make clean

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf wordlistGenerator

wordlistGenerator:	wordlistGenerator.c
	$(CC) $(CFLAGS) wordlistGenerator.c -o wordlistGenerator