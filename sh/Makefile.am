profiledir = /etc/profile.d

bin_SCRIPTS = home-etc

profile_SCRIPTS = home-etc.sh home-etc.csh

dist-local: 
	./home-etc --update
	mv -f home-etc.new home-etc

install: update
	install -d $(DESTDIR)/etc/profile.d
	install -d $(DESTDIR)/usr/bin
	install -m755 home-etc.*sh $(DESTDIR)/etc/profile.d
	install -m755 home-etc $(DESTDIR)/usr/bin
