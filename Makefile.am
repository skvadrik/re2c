# $Id$

bin_PROGRAMS = re2c
re2c_SOURCES = code.cc dfa.cc main.cc parser.cc actions.cc scanner.re substr.cc\
	translate.cc scanner.cc mbo_getopt.cc \
	basics.h dfa.h globals.h ins.h parser.h re.h scanner.h \
	substr.h token.h mbo_getopt.h
man_MANS     = re2c.1
#CXXFLAGS     = -O2 -Wall -I. -Wno-unused -Wno-parentheses -Wno-deprecated
YFLAGS       = -d
RE2C         = re2c
RE2CFLAGS    = -s
CLEANFILES   = parser.cc y.tab.c y.tab.h parser.cc re2c.1 .version
DISTCLEANFILES = makerpm re2c.spec README scanner.cc re2c
EXTRA_DIST   = $(man_MANS) README parser.y scanner.re makerpm.in re2c.spec.in \
               README.in y.tab.h \
               examples/basemmap.c examples/c.re examples/cmmap.re \
			   examples/cnokw.re examples/cunroll.re examples/modula.re \
			   examples/sample.re examples/simple.re examples/rexx/README \
			   examples/rexx/rexx.l examples/rexx/scanio.c doc/loplas.ps \
			   doc/sample.bib website/index.html

rpm-files:	$(bin_PROGRAMS) $(EXTRA_DIST)

parser.cc:	parser.y
	$(YACC) $(YFLAGS) parser.y
	mv -f y.tab.c parser.cc

scanner.cc: scanner.re
	@if test -x ./re2c; then \
		echo "re2c $(RE2CFLAGS) $< >$@.tmp"; \
		./re2c $(RE2CFLAGS) $< >$@.tmp && mv $@.tmp $@ && cp $@ bootstrap/; \
	else \
		echo "cp -f bootstrap/$@ $@"; \
		cp -f bootstrap/$@ $@; \
	fi

.version:
	echo $(PACKAGE_VERSION) > .version
