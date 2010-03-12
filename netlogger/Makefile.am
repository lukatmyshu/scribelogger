## This is the shared library to be built

h_sources = logger.h 
cc_sources = logger.cc

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

AM_CPPFLAGS = $(GLIB_CFLAGS) $(OPENSSL_CFLAGS) $(JSON_CFLAGS)
lib_LTLIBRARIES = libnetlogger-1.la
libnetlogger_1_la_SOURCES = $(h_sources) $(cc_sources)
libnetlogger_1_la_LDFLAGS = $(LIBS) $(GLIB_LIBS) $(OPENSSL_LIBS) -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

#bin_PROGRAMS = controller
#controller_SOURCES = controller.cc
#bin_CPPFLAGS = $(JSON_CFLAGS)
#controller_LDFLAGS = $(LIBS) $(GLIB_LIBS) $(OPENSSL_LIBS) $(JSON_LIBS)
#controller_LDADD = $(lib_LTLIBRARIES)

#check_PROGRAMS = test

#test_SOURCES = test.cc
#test_LDADD = $(lib_LTLIBRARIES)
