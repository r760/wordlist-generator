CC=gcc
CFLAGS=-Wall -g

INCLUDEDIR=include
SRCDIR=src
LIBDIR=lib
BINDIR=bin
CUTILSDIR=cutils
MANDIR=share/man/

CFLAGS+=-I$(INCLUDEDIR)
CFLAGS+=-L$(LIBDIR)

help:	Makefile
	@sed -n 's/^##[ ]*/\n/p' $< | sed 's/: /:\n\t/g; 1d'

## man: open wgen's man page
man:	share/man/wgen.1
	man share/man/wgen.1

## bin/wgen: compile wgen
$(BINDIR)/wgen:	$(SRCDIR)/wgen.c
	make clean
	[ ! -d $(CUTILSDIR) ] && git clone https://github.com/r760/cutils.git || true
	cd $(CUTILSDIR); git pull; make $(LIBDIR)/liblog.a
	mkdir $(INCLUDEDIR)
	cp $(CUTILSDIR)/$(INCLUDEDIR)/log.h $(INCLUDEDIR)
	mkdir $(LIBDIR)
	cp $(CUTILSDIR)/lib/liblog.a $(LIBDIR)
	mkdir $(BINDIR)
	${CC} ${CFLAGS} $^ -llog -o $(BINDIR)/wgen

## example: an example of how to run wgen
example:	$(BINDIR)/wgen
	$(BINDIR)/wgen -o wordlist.txt -min 3 -max 3 -c "ABC"
	
## install: install wgen binary and man file
install:	$(BINDIR)/wgen $(MANDIR)/wgen.1
	[ -d /usr/local/man/man1 ] || sudo mkdir -p /usr/local/man/man1
	[ -d /usr/local/bin ] || sudo mkdir -p /usr/local/bin
	cd $(BINDIR); find . -type f -exec sudo cp -v {} /usr/local/bin/ \;
	cd $(MANDIR); find . -type f -name "*.1" -exec sudo cp -v {} /usr/local/man/man1/ \;

## uninstall: remove wgen binary and man file
uninstall:	$(BINDIR)/wgen $(MANDIR)/wgen.1
	cd $(BINDIR); find . -type f -exec sudo rm -v /usr/local/bin/{} \;
	cd $(MANDIR); find . -type f -name "*.1" -exec sudo rm -v /usr/local/man/man1/{} \;

## clean: include, lib, and bin dirs (and everything inside)
clean:
	[ -d $(CUTILSDIR) ] && cd $(CUTILSDIR) && make clean || true
	rm -rf $(INCLUDEDIR) $(LIBDIR) $(BINDIR) &> /dev/null || true
