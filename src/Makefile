# $Id: Makefile,v 1.4 2003/11/27 17:06:42 siefca Exp $

CC=gcc
CFLAGS=-fPIC -O2 -Wall -Werror -pedantic
CPPFLAGS=-I.
LDFLAGS=-x --shared
OUT=libhome_etc.so
OBJECTS=core.o wrap_fopen.o

all:	$(OUT)

$(OBJECTS): $(OBJECTS:.o=.c)
	$(CC) $(CFLAGS) -o $@ -c $<

lib%.so: %.o
	ld $(LDFLAGS) -o $@ $<

clean:
	rm -f a.out *.o test $(OUT)

install:
	install -d $(DESTDIR)/usr/lib
	install -d $(DESTDIR)/usr/include
	install -s -m755 $(OUT) $(DESTDIR)/usr/lib
	install -m644 home_etc.h $(DESTDIR)/usr/include/home_etc.h
