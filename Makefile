NAME=home_etc
VERSION=1.0.1
LIBNAME=libhome_etc.so

DIRS=sh src skel
FILES=TODO COPYING AUTHORS HOME-ETC.txt README home_etc.spec

all: lib

lib:
	cd src && make

dist:
	$(MAKE) clean
	mkdir $(NAME)-$(VERSION)
	cp -r $(FILES) $(DIRS) Makefile $(NAME)-$(VERSION)
	tar czf $(NAME)-$(VERSION).tar.gz $(NAME)-$(VERSION)
	$(MAKE) distclean

distclean:
	$(MAKE) clean
	rm -rf $(NAME)-$(VERSION)

rpm:
	$(MAKE) dist
	rpmbuild -ta --clean $(NAME)-$(VERSION).tar.gz

install:
	cd src && make install

clean:
	cd src && make clean
