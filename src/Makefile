# $Id: Makefile,v 1.14 2003/12/05 17:21:51 siefca Exp $
NAME=home-etc
VERSION=1.0.1
CC=gcc
RANLIB=ranlib
CFLAGS=-fPIC -O2 -Wall -Werror -pedantic
CPPFLAGS=-I.
LDFLAGS=-x --shared
OUT=libhome_etc.so.1
OUT_STATIC=libhome_etc.a
LA_FILE=libhome_etc.la
OBJECTS=core.o home_etc.o

all:	$(OBJECTS) $(OUT) $(OUT_STATIC)

%.o: %.c
	$(CC) $(CFLAGS) $(RPMCFLAGS) -o $@ -c $<

$(OUT): $(OBJECTS)
	$(CC) -shared -Wl,-soname,$(OUT) -o $(OUT) $(OBJECTS)

$(OUT_STATIC): $(OBJECTS)
	ar -cr $@ $(OBJECTS)
	$(RANLIB) $@

test: core.c test.c
	$(CC) $(CFLAGS) core.c test.c -o test

clean:
	rm -f a.out example *.a *.o test *.so *.so.$(VERSION) *.so.1

install:
	install -d $(DESTDIR)/usr/lib
	install -d $(DESTDIR)/usr/include
	install -d $(DESTDIR)/usr/src/examples/$(NAME)-$(VERSION)
	install -s -m755 $(OUT) $(DESTDIR)/usr/lib
	install -m755 $(OUT_STATIC) $(DESTDIR)/usr/lib
	install -m755 $(LA_FILE) $(DESTDIR)/usr/lib
	ln -s -f $(OUT) $(DESTDIR)/usr/lib/libhome_etc.so
	ln -s -f $(OUT) $(DESTDIR)/usr/lib/libhome_etc.so.$(VERSION)
	install -m644 home_etc.h $(DESTDIR)/usr/include/home_etc.h
	install -m644 example*.c $(DESTDIR)/usr/src/examples/$(NAME)-$(VERSION)
