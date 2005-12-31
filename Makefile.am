# $Id$

bin_PROGRAMS = re2c
re2c_SOURCES = code.cc dfa.cc main.cc parser.cc actions.cc scanner.re substr.cc\
	translate.cc scanner.cc mbo_getopt.cc \
	basics.h dfa.h globals.h ins.h parser.h re.h scanner.h \
	substr.h token.h mbo_getopt.h code.h
BUILT_SOURCES = parser.cc scanner.cc

man_MANS     = re2c.1

#CXXFLAGS     = -O2 -Wall -I. -Wno-unused -Wno-parentheses -Wno-deprecated
YFLAGS       = -d

RE2C         = re2c$(EXEEXT)
RE2CFLAGS    = -s

CLEANFILES   = parser.cc y.tab.c y.tab.h parser.cc re2c.1 .version

DISTCLEANFILES = makerpm re2c.spec README scanner.cc re2c$(EXEEXT)

EXTRA_DIST   = $(man_MANS) README parser.y scanner.re makerpm.in re2c.spec.in \
               re2c.spec README.in y.tab.h CHANGELOG \
               doc examples test

dist-hook: re2c.spec
	cat re2c.spec | sed -e "s/RPM_RELEASE/1/g" > $(distdir)/re2c.spec
	rm -rf `find $(distdir)/doc -name CVS`
	rm -rf `find $(distdir)/examples -name CVS`
	rm -rf `find $(distdir)/test -name CVS`


rpm-files:	$(bin_PROGRAMS) $(EXTRA_DIST)

rpm: dist
	rpmbuild -ta re2c-$(PACKAGE_VERSION).tar.gz

parser.cc:	$(top_srcdir)/parser.y
	$(YACC) $(YFLAGS) $< || exit
	cat y.tab.c | sed 's/"y\.tab\.c"/"parser.cc"/g' > $(top_srcdir)/parser.cc
	rm -f y.tab.c
	if cmp -s $(top_srcdir)/parser.cc $(top_srcdir)/bootstrap/parser.cc; then :; else cp -f $(top_srcdir)/parser.cc $(top_srcdir)/bootstrap/parser.cc; fi
	if cmp -s y.tab.h $(top_srcdir)/y.tab.h; then :; else mv -f y.tab.h $(top_srcdir)/y.tab.h; fi
	if cmp -s $(top_srcdir)/y.tab.h $(top_srcdir)/bootstrap/y.tab.h; then :; else cp -f $(top_srcdir)/y.tab.h $(top_srcdir)/bootstrap/y.tab.h; fi

scanner.cc: $(top_srcdir)/scanner.re
	@if test -x ./re2c$(EXEEXT); then \
		echo "re2c $(RE2CFLAGS) -o $@ $<"; \
		./re2c $(RE2CFLAGS) -o $@ $< && cp $@ $(top_srcdir)/bootstrap/; \
	else \
		echo "cp -f $(top_srcdir)/bootstrap/$@ $@"; \
		cp -f $(top_srcdir)/bootstrap/$@ $@; \
	fi

.version:
	echo $(PACKAGE_VERSION) > .version

TESTS = run_tests.sh

test: all $(TESTS)
	test -x $(TESTS) || chmod +x $(TESTS)
	./$(TESTS)
