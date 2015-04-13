# $Id$

bin_PROGRAMS = re2c
re2c_SOURCES = code.cc dfa.cc main.cc parser.cc actions.cc scanner.re substr.cc range.cc \
	translate.cc scanner.cc mbo_getopt.cc print.cc input_api.cc \
	enc.cc utf8.cc utf8_range.cc utf8_regexp.cc utf16.cc utf16_range.cc utf16_regexp.cc range_suffix.cc \
	basics.h code.h code_names.h dfa.h enc.h indent.h input_api.h free_list.h globals.h ins.h \
	mbo_getopt.h parser.h print.h range.h range_suffix.h re.h \
	scanner.h smart_ptr.h substr.h stream_lc.h token.h \
	utf16.h utf16_range.h utf16_regexp.h utf8.h utf8_range.h utf8_regexp.h
BUILT_SOURCES = parser.cc scanner.cc

#CXXFLAGS     = -O2 -Wall -Wno-unused -Wno-parentheses -Wno-deprecated
#CXXFLAGS     = -ggdb -fno-inline -O2 -Wall -Wextra -pedantic -Wconversion -Wpointer-arith -Wwrite-strings -Wredundant-decls -Werror -Wunused-function -DPEDANTIC
#CXXFLAGS     += -O2
CXXFLAGS     += -W -Wall -Wextra -pedantic -Wredundant-decls -DPEDANTIC
YFLAGS       = -y -d --no-lines

RE2C         = re2c$(EXEEXT)
RE2CFLAGS    = -bi

CLEANFILES = parser.cc y.tab.c y.tab.h scanner.cc .version

DISTCLEANFILES = makerpm re2c.spec README scanner.cc re2c$(EXEEXT)

man_MANS = re2c.1
DOCS = $(man_MANS) htdocs/manual.html

EXTRA_SRC    = README parser.y scanner.re y.tab.h CHANGELOG NO_WARRANTY \
               doc examples test bootstrap/*.cc bootstrap/*.h bootstrap/re2c.1 lessons \
               $(DOCS)
EXTRA_DIST   = $(EXTRA_SRC) makerpm.in re2c.spec.in re2c.spec README.in config_w32.h.in

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

release: dist src-rpm

parser.cc: $(top_srcdir)/parser.y
	@if test $(BISON) = "yes"; then \
		bison $(YFLAGS) --output=$(top_srcdir)/parser.cc --defines=$(top_srcdir)/y.tab.h $(top_srcdir)/parser.y && \
		cp -f $(top_srcdir)/parser.cc $(top_srcdir)/bootstrap/parser.cc; \
		cp -f $(top_srcdir)/y.tab.h $(top_srcdir)/bootstrap/y.tab.h; \
	else \
		cp -f $(top_srcdir)/bootstrap/parser.cc $(top_srcdir)/parser.cc; \
		cp -f $(top_srcdir)/bootstrap/y.tab.h $(top_srcdir)/y.tab.h; \
	fi

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

if REBUILD_DOCS
docs: $(DOCS)
$(DOCS): re2c.ad
	a2x -f manpage re2c.ad
	mkdir -p htdocs
	asciidoc -o htdocs/manual.html re2c.ad
	cp re2c.1 $(top_srcdir)/bootstrap/re2c.1
else
docs: $(DOCS)
$(DOCS): $(top_srcdir)/bootstrap/re2c.1
	@echo "Reconfigure to rebuild docs: ./configure --enable-docs"
	cp $(top_srcdir)/bootstrap/re2c.1 $(top_srcdir)/re2c.1
endif
