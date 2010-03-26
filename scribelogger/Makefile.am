## This is the shared library to be built

h_sources = logger.h
cc_sources = logger.cc scribe.cc scribe_constants.cc scribe_types.cc

library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)-$(GENERIC_API_VERSION)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)

AM_CPPFLAGS = $(GLIB_CFLAGS) $(THRIFT_CFLAGS) -I/usr/include/thrift/fb303 -Wall -Werror -O3
lib_LTLIBRARIES = libscribelogger-1.la
libscribelogger_1_la_SOURCES = $(h_sources) $(cc_sources)
libscribelogger_1_la_LDFLAGS = $(LIBS) $(GLIB_LIBS) $(GTHREAD_LIBS) $(THRIFT_LIBS) -lfb303 $(OP -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)
