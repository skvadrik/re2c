# $Id$

bin_PROGRAMS = re2c
re2c_SOURCES = code.cc dfa.cc main.cc parser.cc actions.cc scanner.re substr.cc\
	translate.cc scanner.cc
man_MANS     = re2c.1
CXXFLAGS     = -O2 -Wall -I. -Wno-unused -Wno-parentheses -Wno-deprecated
YFLAGS       = -d
CLEANFILES   = y.tab.c y.tab.h parser.cc re2c.1 version.h .version makerpm
EXTRA_DIST   = $(man_MANS) README

rpm-files:	$(bin_PROGRAMS) $(EXTRA_DIST)

main.cc:	version.h

parser.cc:	version.h parser.y
	$(YACC) $(YFLAGS) parser.y
	mv -f y.tab.c parser.cc

scanner.cc: scanner.re
	-@if test -x re2c; then \
		echo "re2c -s $< >$@"; \
		re2c -s $< >$@; \
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

README:
	cat README.in | sed 's/RE2C_VERSION/$(PACKAGE_VERSION)/g' > README

makerpm:
	cat makerpm.in | sed 's/RE2C_VERSION/$(PACKAGE_VERSION)/g' > makerpm
	chmod +x makerpm

re2c.1:
	cat re2c.1.in | sed 's/RE2C_VERSION/$(PACKAGE_VERSION)/g' > re2c.1

