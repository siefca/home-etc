profiledir = /etc/profile.d

dist_bin_SCRIPTS = home-etc
dist_profile_SCRIPTS = home-etc.sh home-etc.csh

dist-local:
	./home-etc --update
	mv -f home-etc.new home-etc

install: dist-local
	$(mkinstalldirs) $(DESTDIR)$(profiledir)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	$(install_sh_SCRIPT) home-etc.*sh $(DESTDIR)$(profiledir)
	$(install_sh_SCRIPT) home-etc $(DESTDIR)$(bindir)
