profiledir = @prefix@/etc/profile.d

bin_SCRIPTS = home-etc
profile_SCRIPTS = home-etc.sh home-etc.csh

EXTRA_DIST = $(SCRIPTS)

dist-local:
	./home-etc --update
	mv -f home-etc.new home-etc

install: dist-local
	$(mkinstalldirs) $(DESTDIR)$(profiledir)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	install -m755 home-etc.*sh $(DESTDIR)$(profiledir)
	install -m755 home-etc $(DESTDIR)$(bindir)
