# $Id$

bin_PROGRAMS = re2c
win_BINARIES = $(WINBUILDDIR)/re2c.exe
re2c_SOURCES = code.cc dfa.cc main.cc parser.cc actions.cc scanner.re substr.cc range.cc \
	translate.cc scanner.cc mbo_getopt.cc print.cc \
	enc.cc utf8.cc utf8_range.cc utf8_regexp.cc utf16.cc utf16_range.cc utf16_regexp.cc range_suffix.cc \
	basics.h code.h code_names.h dfa.h enc.h free_list.h globals.h ins.h \
	mbo_getopt.h parser.h print.h range.h range_suffix.h re.h \
	scanner.h smart_ptr.h substr.h stream_lc.h token.h \
	utf16.h utf16_range.h utf16_regexp.h utf8.h utf8_range.h utf8_regexp.h
BUILT_SOURCES = parser.cc scanner.cc

#CXXFLAGS     = -O2 -Wall -Wno-unused -Wno-parentheses -Wno-deprecated
#CXXFLAGS     = -ggdb -fno-inline -O2 -Wall -Wextra -pedantic -Wconversion -Wpointer-arith -Wwrite-strings -Wredundant-decls -Werror -Wunused-function -DPEDANTIC
#CXXFLAGS     += -O2
CXXFLAGS     += -W -Wall -Wextra -pedantic -Wredundant-decls -DPEDANTIC
YFLAGS       = -d

RE2C         = re2c$(EXEEXT)
RE2CFLAGS    = -bi

CLEANFILES = parser.cc y.tab.c y.tab.h scanner.cc .version
if HAVE_ASCIIDOC
    CLEANFILES += htdocs/manual.html
endif HAVE_ASCIIDOC
if HAVE_A2X
    CLEANFILES += re2c.1
endif HAVE_A2X

DISTCLEANFILES = makerpm re2c.spec README scanner.cc re2c$(EXEEXT)

man_MANS = re2c.1
DOCS = $(man_MANS) htdocs/manual.html

EXTRA_SRC    = README parser.y scanner.re y.tab.h CHANGELOG NO_WARRANTY \
               doc examples test bootstrap/*.cc bootstrap/*.h lessons \
               $(DOCS)
EXTRA_DIST   = $(EXTRA_SRC) makerpm.in re2c.spec.in re2c.spec README.in config_w32.h.in
EXTRA_ZIP    = $(EXTRA_SRC) config_w32.h *.sln *.vcproj re2c.rules

dist-hook: re2c.spec
	rm -rf `find $(distdir)/doc -name .git`
	rm -rf `find $(distdir)/examples -name .git`
	rm -rf `find $(distdir)/test -name .git -o -name .gitignore`
	rm -rf `find $(distdir)/lessons -name .git -o -name .gitignore`

rpm-files: $(bin_PROGRAMS) $(EXTRA_DIST)

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
	zipinfo -1      re2c-$(PACKAGE_VERSION)-src.zip | grep .git | xargs zip -d re2c-$(PACKAGE_VERSION)-src.zip >/dev/null
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

tests: all $(TESTS)
	test -x $(TESTS) || chmod +x $(TESTS)
	./$(TESTS)

vtests: all $(TESTS)
	test -x $(TESTS) || chmod +x $(TESTS)
	./$(TESTS) --valgrind

docs: $(DOCS)
$(DOCS): re2c.ad
	@if test $(A2X) = "yes"; then \
		a2x -f manpage re2c.ad; \
	fi
	@if test $(ASCIIDOC) = "yes"; then \
		mkdir -p htdocs; \
		asciidoc -o htdocs/manual.html re2c.ad; \
	fi
