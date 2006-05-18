lib_LTLIBRARIES = libhome_etc.la
examplesdir=@prefix@/src/examples/$(PACKAGE)-$(VERSION)

libhome_etc_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

libhome_etc_la_SOURCES = \
						 core.c \
						 core.h \
						 includes.h \
						 home_etc.c
include_HEADERS = home_etc.h

realpath_SOURCES = realpath.c

noinst_PROGRAMS = test example example2 example3 example4

bin_PROGRAMS = realpath

test_LDADD = libhome_etc.la
realpath_LDADD = libhome_etc.la
example_LDADD = libhome_etc.la
example2_LDADD = libhome_etc.la
example3_LDADD = libhome_etc.la
example4_LDADD = libhome_etc.la

TESTS=test

examples = \
						example.c \
						example2.c \
						example3.c \
						example4.c

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(examplesdir)
	$(INSTALL_DATA) $(examples) $(DESTDIR)$(examplesdir)
