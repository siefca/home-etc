NAME=home_etc
VERSION=0.1
LIBNAME=libhome_etc.so

DIRS=doc sh src skel
FILES=COPYING AUTHORS

all: lib dist rpm

lib:
	cd src && make

dist:
	$(MAKE) clean
	$(MAKE) lib
	mkdir $(NAME)-$(VERSION)
	cp -r $(FILES) $(DIRS) Makefile $(NAME)-$(VERSION)
	tar czf $(NAME)-$(VERSION).tar.gz $(NAME)-$(VERSION)

distclean:
	$(MAKE) clean
	rm -rf $(NAME)-$(VERSION) 

rpm:
	$(MAKE) dist

install:
	cd src && make install

clean:
	cd src && make clean
