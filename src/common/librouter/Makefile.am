AM_CFLAGS = \
        $(WARNING_CFLAGS) \
        $(CODE_COVERAGE_CFLAGS)

AM_LDFLAGS = \
        $(CODE_COVERAGE_LDFLAGS)

AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/src/include \
	-I$(top_builddir)/src/common/libflux \
	$(ZMQ_CFLAGS)

noinst_LTLIBRARIES = \
	librouter.la

librouter_la_SOURCES = \
	sendfd.h \
	sendfd.c \
	auth.c \
	auth.h \
	usock.c \
	usock.h \
	disconnect.h \
	disconnect.c \
	subhash.h \
	subhash.c \
	servhash.h \
	servhash.c \
	router.h \
	router.c

TESTS = \
	test_sendfd.t \
        test_disconnect.t \
	test_auth.t \
	test_usock.t \
	test_usock_echo.t \
	test_subhash.t \
	test_router.t \
	test_servhash.t

check_PROGRAMS = \
        $(TESTS)

check_LTLIBRARIES = libtestutil.la

libtestutil_la_SOURCES = \
        test/usock_util.c \
        test/usock_util.h

TEST_EXTENSIONS = .t
T_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
        $(top_srcdir)/config/tap-driver.sh

test_ldadd = \
	$(builddir)/libtestutil.la \
        $(top_builddir)/src/common/librouter/librouter.la \
        $(top_builddir)/src/common/libtestutil/libtestutil.la \
        $(top_builddir)/src/common/libflux-internal.la \
        $(top_builddir)/src/common/libflux-core.la \
        $(top_builddir)/src/common/libtap/libtap.la

test_cppflags = \
        $(AM_CPPFLAGS) \
        -I$(top_srcdir)/src/common/libtap

test_sendfd_t_SOURCES = test/sendfd.c
test_sendfd_t_CPPFLAGS = $(test_cppflags)
test_sendfd_t_LDADD = $(test_ldadd)

test_disconnect_t_SOURCES = test/disconnect.c
test_disconnect_t_CPPFLAGS = $(test_cppflags)
test_disconnect_t_LDADD = $(test_ldadd)

test_auth_t_SOURCES = test/auth.c
test_auth_t_CPPFLAGS = $(test_cppflags)
test_auth_t_LDADD = $(test_ldadd)

test_usock_t_SOURCES = test/usock.c
test_usock_t_CPPFLAGS = $(test_cppflags)
test_usock_t_LDADD = $(test_ldadd)

test_usock_echo_t_SOURCES = test/usock_echo.c
test_usock_echo_t_CPPFLAGS = $(test_cppflags)
test_usock_echo_t_LDADD = $(test_ldadd)

test_subhash_t_SOURCES = test/subhash.c
test_subhash_t_CPPFLAGS = $(test_cppflags)
test_subhash_t_LDADD = $(test_ldadd)

test_router_t_SOURCES = test/router.c
test_router_t_CPPFLAGS = $(test_cppflags)
test_router_t_LDADD = $(test_ldadd)

test_servhash_t_SOURCES = test/servhash.c
test_servhash_t_CPPFLAGS = $(test_cppflags)
test_servhash_t_LDADD = $(test_ldadd)
