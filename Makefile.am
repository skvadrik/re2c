# $Id$

bin_PROGRAMS = re2c
re2c_SOURCES = code.cc dfa.cc main.cc parser.cc actions.cc scanner.re substr.cc\
	translate.cc scanner.cc
include_HEADERS=basics.h dfa.h globals.h ins.h parser.h re.h scanner.h \
	substr.h token.h version.h
man_MANS    = re2c.1
CXXFLAGS     = -O2 -Wall -I. -Wno-unused -Wno-parentheses -Wno-deprecated
YFLAGS       = -d
RE2C         = re2c
RE2CFLAGS    =
CLEANFILES   = y.tab.c y.tab.h parser.cc re2c.1 version.h .version \
DISTCLEANFILES = makerpm re2c*.spec README scanner.cc re2c
EXTRA_DIST   = $(man_MANS) README parser.y scanner.re

rpm-files:	$(bin_PROGRAMS) $(EXTRA_DIST)

main.cc:	version.h

parser.cc:	version.h parser.y
	$(YACC) $(YFLAGS) parser.y
	mv -f y.tab.c parser.cc

scanner.cc: scanner.re
	-@if test -x ./re2c; then \
		echo "re2c -s $< >$@"; \
		./re2c -s $< >$@; \
	else \
		echo "cp -f bootstrap/$@ $@"; \
		cp -f bootstrap/$@ $@; \
	fi

re2c.ps:
	gunzip -c doc/loplas.ps.gz > re2c.ps

.version:
	echo $(PACKAGE_VERSION) > .version

version.h:
	echo "#define RE2C_VERSION \"$(PACKAGE_VERSION)\"" > version.h

