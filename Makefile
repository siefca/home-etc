NAME=home-etc
VERSION=1.0.3
LIBNAME=libhome_etc.so

DIRS=sh src skel patchwork
FILES=FILES TODO COPYING AUTHORS CONTRIBUTORS HOME-ETC.txt README home-etc.spec

all: lib

lib:
	cd src && make NAME=$(NAME) VERSION=$(VERSION);

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

publish:
	$(MAKE) distclean
	$(MAKE) dist
	scp $(NAME)-$(VERSION).tar.gz siefca@kernel.pl:~/ftp-pld/distfiles
	ssh siefca@kernel.pl 'chmod a+r ~/ftp-pld/distfiles/*'
