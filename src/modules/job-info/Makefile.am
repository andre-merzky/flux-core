AM_CFLAGS = \
	$(WARNING_CFLAGS) \
	$(CODE_COVERAGE_CFLAGS)

AM_LDFLAGS = \
	$(CODE_COVERAGE_LIBS)

AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/src/include \
	-I$(top_builddir)/src/common/libflux \
	$(ZMQ_CFLAGS) $(FLUX_SECURITY_CFLAGS) $(YAMLCPP_CFLAGS)

fluxmod_LTLIBRARIES = job-info.la

job_info_la_SOURCES = \
	job-info.c \
	info.h \
	allow.h \
	allow.c \
	job_state.h \
	job_state.c \
	list.h \
	list.c \
	lookup.h \
	lookup.c \
	watch.h \
	watch.c \
	guest_watch.h \
	guest_watch.c

job_info_la_LDFLAGS = $(fluxmod_ldflags) -module
job_info_la_LIBADD = $(fluxmod_libadd) \
	$(top_builddir)/src/common/libjob/libjob.la \
	$(top_builddir)/src/common/libflux-internal.la \
	$(top_builddir)/src/common/libflux-core.la \
	$(top_builddir)/src/common/libflux-optparse.la \
	$(ZMQ_LIBS)
