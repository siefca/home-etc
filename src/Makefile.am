lib_LTLIBRARIES = libhome_etc.la

libhome_etc_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

libhome_etc_la_SOURCES = \
						 core.c \
						 core.h \
						 home_etc.c
include_HEADERS = home_etc.h

noinst_PROGRAMS = test example example2 example3 

test_LDADD = libhome_etc.la
example_LDADD = libhome_etc.la
example2_LDADD = libhome_etc.la
example3_LDADD = libhome_etc.la

TESTS=test
