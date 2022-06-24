CC=gcc
CFLAGS=-Wall -g

INCLUDEDIR=include
SRCDIR=src
LIBDIR=lib
BINDIR=bin
CUTILSDIR=cutils

CFLAGS+=-I$(INCLUDEDIR)
CFLAGS+=-L$(LIBDIR)

help:	Makefile
	@sed -n 's/^##[ ]*/\n/p' $< | sed 's/: /:\n\t/g; 1d'

## clean: remove cutils, include, lib, and bin dirs (and everything inside)
clean:
	rm -rf $(CUTILSDIR) $(INCLUDEDIR) $(LIBDIR) $(BINDIR) &> /dev/null || true

## man: open wgen's man page
man:	share/man/wgen.1
	man share/man/wgen.1

cutils:
	git clone https://github.com/r760/cutils.git
	cd $(CUTILSDIR); make $(LIBDIR)/liblog.a

## bin/wgen: compile wgen
$(BINDIR)/wgen:	$(SRCDIR)/wgen.c
	make clean
	make cutils
	mkdir $(INCLUDEDIR)
	cp $(CUTILSDIR)/$(INCLUDEDIR)/log.h $(INCLUDEDIR)
	mkdir $(LIBDIR)
	cp $(CUTILSDIR)/lib/liblog.a $(LIBDIR)
	mkdir $(BINDIR)
	${CC} ${CFLAGS} $^ -llog -o $(BINDIR)/wgen

## example: an example of how to run wgen
example:	$(BINDIR)/wgen
	$(BINDIR)/wgen -o wordlist.txt -min 3 -max 3 -c "ABC"
