# $Id: Makefile,v 1.1 2003/11/26 18:10:58 siefca Exp $

CC=gcc
CFLAGS=-fPIC -O2 -Wall -Werror -pedantic
CPPFLAGS=-I.
LDFLAGS=-x --shared
OUT=libhome_etc.so

all:	$(OUT)

lib%.so: %.o
	ld $(LDFLAGS) -o $@ $<

clean:
	rm -f a.out *.o test $(OUT)

install:
	install -s -o0 -g0 -m755 $(OUT) /usr/lib
	install -m644 home_etc.h /usr/include/home_etc.h
