# $Id$

AM_CXXFLAGS = -W -Wall -Wextra -pedantic -Wredundant-decls -DPEDANTIC -O2
AM_YFLAGS = -y -d --no-lines
RE2CFLAGS = -bi

bin_PROGRAMS = re2c
RE2C = $(builddir)/re2c$(EXEEXT)

# scanner
SRC_SCANNER = $(srcdir)/src/scanner.re
AUTOGEN_SCANNER = $(builddir)/scanner.cc
BOOTSTRAP_SCANNER = $(srcdir)/bootstrap/scanner.cc

# parser
SRC_PARSER = $(srcdir)/src/parser.ypp
AUTOGEN_PARSER = $(builddir)/parser.cc
AUTOGEN_PARSER_HDR = $(builddir)/y.tab.h
BOOTSTRAP_PARSER = $(srcdir)/bootstrap/parser.cc
BOOTSTRAP_PARSER_HDR = $(srcdir)/bootstrap/y.tab.h

# docs
DOC_MAN = $(builddir)/doc/re2c.1
DOC_HTML = $(builddir)/doc/manual.html
SRC_DOC = $(builddir)/doc/re2c.ad
BOOTSTRAP_DOC_MAN = $(srcdir)/bootstrap/re2c.1
BOOTSTRAP_DOC_HTML = $(srcdir)/bootstrap/manual.html

SRC_HDR = \
	$(srcdir)/src/c99_stdint.h \
	$(srcdir)/src/code.h \
	$(srcdir)/src/code_names.h \
	$(srcdir)/src/dfa.h \
	$(srcdir)/src/enc.h \
	$(srcdir)/src/globals.h \
	$(srcdir)/src/go.h \
	$(srcdir)/src/indent.h \
	$(srcdir)/src/input.h \
	$(srcdir)/src/input_api.h \
	$(srcdir)/src/ins.h \
	$(srcdir)/src/free_list.h \
	$(srcdir)/src/mbo_getopt.h \
	$(srcdir)/src/output.h \
	$(srcdir)/src/parser.h \
	$(srcdir)/src/print.h \
	$(srcdir)/src/range.h \
	$(srcdir)/src/range_suffix.h \
	$(srcdir)/src/re.h \
	$(srcdir)/src/scanner.h \
	$(srcdir)/src/skeleton.h \
	$(srcdir)/src/smart_ptr.h \
	$(srcdir)/src/substr.h \
	$(srcdir)/src/token.h \
	$(srcdir)/src/utf16.h \
	$(srcdir)/src/utf16_range.h \
	$(srcdir)/src/utf16_regexp.h \
	$(srcdir)/src/utf8.h \
	$(srcdir)/src/utf8_range.h \
	$(srcdir)/src/utf8_regexp.h

SRC = \
	$(SRC_SCANNER) \
	$(srcdir)/src/actions.cc \
	$(srcdir)/src/code.cc \
	$(srcdir)/src/code_names.cc \
	$(srcdir)/src/dfa.cc \
	$(srcdir)/src/enc.cc \
	$(srcdir)/src/go_construct.cc \
	$(srcdir)/src/go_destruct.cc \
	$(srcdir)/src/go_emit.cc \
	$(srcdir)/src/go_used_labels.cc \
	$(srcdir)/src/input.cc \
	$(srcdir)/src/input_api.cc \
	$(srcdir)/src/main.cc \
	$(srcdir)/src/mbo_getopt.cc \
	$(srcdir)/src/output.cc \
	$(srcdir)/src/print.cc \
	$(srcdir)/src/range.cc \
	$(srcdir)/src/range_suffix.cc \
	$(srcdir)/src/skeleton.cc \
	$(srcdir)/src/substr.cc \
	$(srcdir)/src/translate.cc \
	$(srcdir)/src/utf8.cc \
	$(srcdir)/src/utf8_range.cc \
	$(srcdir)/src/utf8_regexp.cc \
	$(srcdir)/src/utf16.cc \
	$(srcdir)/src/utf16_range.cc \
	$(srcdir)/src/utf16_regexp.cc
# omit SRC_PARSER here; include it in EXTRA_DIST instead
# (automake generates standard build rules for all YACC-ish
# sources, they will conflict with our custom build rule).

AUTOGEN = \
	$(AUTOGEN_PARSER) \
	$(AUTOGEN_PARSER_HDR) \
	$(AUTOGEN_SCANNER)

BOOTSTRAP = \
	$(BOOTSTRAP_DOC_HTML) \
	$(BOOTSTRAP_DOC_MAN) \
	$(BOOTSTRAP_PARSER) \
	$(BOOTSTRAP_PARSER_HDR) \
	$(BOOTSTRAP_SCANNER)

re2c_SOURCES = \
	$(SRC_HDR) \
	$(SRC)
nodist_re2c_SOURCES = $(AUTOGEN)

EXTRA_DIST = \
	$(BOOTSTRAP) \
	$(SRC_PARSER) \
	$(srcdir)/CHANGELOG \
	$(srcdir)/NO_WARRANTY \
	$(srcdir)/README \
	$(srcdir)/autogen.sh \
	$(srcdir)/doc/index.html \
	$(srcdir)/doc/loplas.ps \
	$(srcdir)/doc/sample.bib \
	$(srcdir)/examples \
	$(srcdir)/test

CLEANFILES = \
	$(AUTOGEN) \
	$(DOC_HTML) \
	$(DOC_MAN)

TESTS = $(builddir)/run_tests.sh

man_MANS = $(DOC_MAN)

$(AUTOGEN_PARSER): $(SRC_PARSER)
	@if test $(BISON) = "yes"; \
	then \
		bison $(YFLAGS) --output=$(AUTOGEN_PARSER) --defines=$(AUTOGEN_PARSER_HDR) $(SRC_PARSER) && \
		cp $(AUTOGEN_PARSER) $(BOOTSTRAP_PARSER) && \
		cp $(AUTOGEN_PARSER_HDR) $(BOOTSTRAP_PARSER_HDR); \
	else \
		cp $(BOOTSTRAP_PARSER) $(AUTOGEN_PARSER) && \
		cp $(BOOTSTRAP_PARSER_HDR) $(AUTOGEN_PARSER_HDR); \
	fi

$(AUTOGEN_SCANNER): $(SRC_SCANNER)
	@if test -x $(RE2C); \
	then \
		$(RE2C) $(RE2CFLAGS) -o $(AUTOGEN_SCANNER) $(SRC_SCANNER) && \
		cp $(AUTOGEN_SCANNER) $(BOOTSTRAP_SCANNER); \
	else \
		cp $(BOOTSTRAP_SCANNER) $(AUTOGEN_SCANNER); \
	fi

# rebuild lexer (just in case it was bootstrapped) and rebuild re2c
.PHONY: bootstrap
bootstrap: all
	rm $(AUTOGEN_SCANNER)
	$(RE2C) $(RE2CFLAGS) -o $(AUTOGEN_SCANNER) $(SRC_SCANNER)
	cp $(AUTOGEN_SCANNER) $(BOOTSTRAP_SCANNER)
	make all

.PHONY: tests
tests: all $(TESTS)
	./$(TESTS)
.PHONY: vtests
vtests: all $(TESTS)
	./$(TESTS) --valgrind
.PHONY: wtests
wtests: all $(TESTS)
	./$(TESTS) --wine -j1

.PHONY: docs
if REBUILD_DOCS
docs: $(DOC_MAN) $(DOC_HTML)
$(DOC_MAN): $(SRC_DOC)
	a2x -f manpage $(SRC_DOC)
	cp $(DOC_MAN) $(BOOTSTRAP_DOC_MAN)
$(DOC_HTML): $(SRC_DOC)
	asciidoc -o $(DOC_HTML) $(SRC_DOC)
	cp $(DOC_HTML) $(BOOTSTRAP_DOC_HTML)
else
docs: $(DOC_MAN) $(DOC_HTML)
	@echo "Reconfigure to rebuild docs: ./configure --enable-docs"
$(DOC_MAN): $(BOOTSTRAP_DOC_MAN)
	cp $(BOOTSTRAP_DOC_MAN) $(DOC_MAN)
$(DOC_HTML): $(BOOTSTRAP_DOC_HTML)
	cp $(BOOTSTRAP_DOC_HTML) $(DOC_HTML)
endif

all-local: docs
