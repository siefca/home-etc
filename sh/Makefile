
all:	update

update: home-etc
	./home-etc --update
	mv -f home-etc.new home-etc

install: update
	install -d $(DESTDIR)/etc/profile.d
	install -d $(DESTDIR)/usr/bin
	install -m755 home-etc.*sh $(DESTDIR)/etc/profile.d
	install -m755 home-etc $(DESTDIR)/usr/bin
