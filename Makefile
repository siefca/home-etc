NAME=home-etc
VERSION=1.0.1
LIBNAME=libhome_etc.so

DIRS=sh src skel
FILES=FILES TODO COPYING AUTHORS CONTRIBUTORS HOME-ETC.txt README home-etc.spec

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
	for i in $(DIRS); do \
	cd $$i && make install NAME=$(NAME) VERSION=$(VERSION); \
	cd -; \
	done;

clean:
	cd src && make clean
