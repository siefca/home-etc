# $Id: Makefile,v 1.7 2003/11/28 12:51:13 siefca Exp $

CC=gcc
CFLAGS=-fPIC -O2 -Wall -Werror -pedantic
CPPFLAGS=-I.
LDFLAGS=-x --shared
OUT=libhome_etc.so
OBJECTS=core.o

all:	$(OBJECTS) $(OUT)

$(OBJECTS): $(OBJECTS:.o=.c)
	$(CC) $(CFLAGS) -o $@ -c $<

lib%.so: %.o
	ld $(LDFLAGS) -o $@ $<

test: core.c test.c
	$(CC) $(CFLAGS) core.c test.c -o test

clean:
	rm -f a.out *.o test $(OUT)

install:
	install -d $(DESTDIR)/usr/lib
	install -d $(DESTDIR)/usr/include
	install -s -m755 $(OUT) $(DESTDIR)/usr/lib
	install -m644 home_etc.h $(DESTDIR)/usr/include/home_etc.h
