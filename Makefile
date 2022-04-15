CC=gcc
CFLAGS=-Wall -g

help:	Makefile
	@sed -n 's/^##[ ]*//p' $<

## clean:	remove wgen binary
clean:
	rm -rf wgen

## man:	open wgen's man page
man:	wgen.1
	man ./wgen.1

## wgen:	compile wgen
wgen:	wgen.c
	${CC} ${CFLAGS} $^ -o wgen
