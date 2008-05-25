# $Id$

bin_PROGRAMS = re2c
win_BINARIES = $(WINBUILDDIR)/re2c.exe
re2c_SOURCES = code.cc dfa.cc main.cc parser.cc actions.cc scanner.re substr.cc\
	translate.cc scanner.cc mbo_getopt.cc \
	basics.h dfa.h globals.h ins.h parser.h re.h scanner.h \
	substr.h token.h mbo_getopt.h code.h stream_lc.h code_names.h
BUILT_SOURCES = parser.cc scanner.cc

man_MANS     = re2c.1

#CXXFLAGS     = -O2 -Wall -Wno-unused -Wno-parentheses -Wno-deprecated
#CXXFLAGS     = -ggdb -fno-inline -O2 -Wall -Wextra -pedantic -Wconversion -Wpointer-arith -Wwrite-strings -Wredundant-decls -Werror -Wunused-function -DPEDANTIC
YFLAGS       = -d

RE2C         = re2c$(EXEEXT)
RE2CFLAGS    = -bi

CLEANFILES   = parser.cc y.tab.c y.tab.h scanner.cc re2c.1 .version htdocs/manual.html

DISTCLEANFILES = makerpm re2c.spec README scanner.cc re2c$(EXEEXT)

EXTRA_SRC    = $(man_MANS) README parser.y scanner.re y.tab.h CHANGELOG \
               doc examples test bootstrap/*.cc bootstrap/*.h lessons
EXTRA_DIST   = $(EXTRA_SRC) makerpm.in re2c.spec.in re2c.spec README.in config_w32.h.in htdocs/manual.html.in
EXTRA_ZIP    = $(EXTRA_SRC) config_w32.h *.sln *.vcproj re2c.rules

dist-hook: vtest re2c.spec
	rm -rf `find $(distdir)/doc -name .svn`
	rm -rf `find $(distdir)/examples -name .svn`
	rm -rf `find $(distdir)/test -name .svn -o -name .cvsignore`
	rm -rf `find $(distdir)/lessons -name .svn -o -name .cvsignore`

rpm-files:	$(bin_PROGRAMS) $(EXTRA_DIST)

rpm: dist
	cp -f re2c-$(PACKAGE_VERSION).tar.gz `rpm --eval "%{_sourcedir}"`
	cp -f re2c.spec `rpm --eval "%{_specdir}"`
	rpmbuild -ba re2c.spec

src-rpm: dist
	cp -f re2c-$(PACKAGE_VERSION).tar.gz `rpm --eval "%{_sourcedir}"`
	cp -f re2c.spec `rpm --eval "%{_specdir}"`
	rpmbuild -bs re2c.spec
	cp -f `rpm --eval "%{_srcrpmdir}"`/re2c-$(PACKAGE_VERSION)-$(PACKAGE_RELEASE).src.rpm .

zip: $(bin_PROGRAMS) $(EXTRA_ZIP)
	if test -f re2c-$(PACKAGE_VERSION)-src.zip; then rm -f re2c-$(PACKAGE_VERSION)-src.zip; fi
	zip -q -o -9 -r re2c-$(PACKAGE_VERSION)-src.zip $(re2c_SOURCES) $(EXTRA_ZIP)
	zipinfo -1      re2c-$(PACKAGE_VERSION)-src.zip | grep .svn | xargs zip -d re2c-$(PACKAGE_VERSION)-src.zip >/dev/null
	zipinfo -1      re2c-$(PACKAGE_VERSION)-src.zip | grep .cvsignore | xargs zip -d re2c-$(PACKAGE_VERSION)-src.zip >/dev/null
	if test -f re2c-$(PACKAGE_VERSION)-bin.zip; then rm -f re2c-$(PACKAGE_VERSION)-bin.zip; fi
	if test -f $(WINBUILDDIR)/re2c.exe; then \
	zip -q -o -9 -j re2c-$(PACKAGE_VERSION)-bin.zip $(win_BINARIES); \
	fi;

release: dist zip src-rpm

parser.cc: $(top_srcdir)/parser.y
	$(YACC) $(YFLAGS) $(top_srcdir)/parser.y || exit
	cat y.tab.c | sed -e 's/"y\.tab\.c"/"parser.cc"/g' -e 's/"\.\/parser\.y"/"parser.y"/g' > $(top_srcdir)/parser.cc
	rm -f y.tab.c
	mv -f y.tab.h y.tab.c
	cat y.tab.c | sed -e 's/"\.\/parser\.y"/"parser.y"/g' > y.tab.h
	rm -f y.tab.c
	if cmp -s $(top_srcdir)/parser.cc $(top_srcdir)/bootstrap/parser.cc; then :; else cp -f $(top_srcdir)/parser.cc $(top_srcdir)/bootstrap/parser.cc; fi
	if cmp -s y.tab.h $(top_srcdir)/y.tab.h; then :; else mv -f y.tab.h $(top_srcdir)/y.tab.h; fi
	if cmp -s $(top_srcdir)/y.tab.h $(top_srcdir)/bootstrap/y.tab.h; then :; else cp -f $(top_srcdir)/y.tab.h $(top_srcdir)/bootstrap/y.tab.h; fi

scanner.cc: $(top_srcdir)/scanner.re
	@if test -x ./re2c$(EXEEXT); then \
		echo "re2c $(RE2CFLAGS) -o $@ $(top_srcdir)/scanner.re"; \
		./re2c $(RE2CFLAGS) -o $@ $(top_srcdir)/scanner.re && cp $@ $(top_srcdir)/bootstrap/; \
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

vtest: all $(TESTS)
	test -x $(TESTS) || chmod +x $(TESTS)
	./$(TESTS) --valgrind
