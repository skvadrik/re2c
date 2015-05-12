# $Id$

AM_CXXFLAGS = -W -Wall -Wextra -pedantic -Wredundant-decls -DPEDANTIC -O2
AM_YFLAGS = -y -d --no-lines
RE2CFLAGS = -bi

bin_PROGRAMS = re2c
RE2C = $(builddir)/re2c$(EXEEXT)

# scanner
SRC_SCANNER = $(srcdir)/src/parse/scanner_lex.re
AUTOGEN_SCANNER = $(builddir)/scanner_lex.cc
BOOTSTRAP_SCANNER = $(srcdir)/bootstrap/scanner_lex.cc

# parser
SRC_PARSER = $(srcdir)/src/parse/parser.ypp
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
	$(srcdir)/src/codegen/bitmap.h \
	$(srcdir)/src/codegen/code_names.h \
	$(srcdir)/src/codegen/go.h \
	$(srcdir)/src/codegen/indent.h \
	$(srcdir)/src/codegen/input_api.h \
	$(srcdir)/src/codegen/output.h \
	$(srcdir)/src/codegen/print.h \
	$(srcdir)/src/codegen/scc.h \
	$(srcdir)/src/codegen/skeleton/skeleton.h \
	$(srcdir)/src/dfa/encoding/enc.h \
	$(srcdir)/src/dfa/encoding/range_suffix.h \
	$(srcdir)/src/dfa/encoding/utf16/utf16.h \
	$(srcdir)/src/dfa/encoding/utf16/utf16_range.h \
	$(srcdir)/src/dfa/encoding/utf16/utf16_regexp.h \
	$(srcdir)/src/dfa/encoding/utf8/utf8.h \
	$(srcdir)/src/dfa/encoding/utf8/utf8_range.h \
	$(srcdir)/src/dfa/encoding/utf8/utf8_regexp.h \
	$(srcdir)/src/dfa/dfa.h \
	$(srcdir)/src/dfa/ins.h \
	$(srcdir)/src/dfa/re.h \
	$(srcdir)/src/globals.h \
	$(srcdir)/src/mbo_getopt.h \
	$(srcdir)/src/parse/input.h \
	$(srcdir)/src/parse/parser.h \
	$(srcdir)/src/parse/scanner.h \
	$(srcdir)/src/parse/token.h \
	$(srcdir)/src/util/c99_stdint.h \
	$(srcdir)/src/util/free_list.h \
	$(srcdir)/src/util/range.h \
	$(srcdir)/src/util/smart_ptr.h \
	$(srcdir)/src/util/substr.h

SRC = \
	$(SRC_SCANNER) \
	$(srcdir)/src/codegen/bitmap.cc \
	$(srcdir)/src/codegen/code_names.cc \
	$(srcdir)/src/codegen/dfa_emit.cc \
	$(srcdir)/src/codegen/dfa_prepare.cc \
	$(srcdir)/src/codegen/go_construct.cc \
	$(srcdir)/src/codegen/go_destruct.cc \
	$(srcdir)/src/codegen/go_emit.cc \
	$(srcdir)/src/codegen/go_used_labels.cc \
	$(srcdir)/src/codegen/input_api.cc \
	$(srcdir)/src/codegen/output.cc \
	$(srcdir)/src/codegen/print.cc \
	$(srcdir)/src/codegen/scc.cc \
	$(srcdir)/src/codegen/skeleton/skeleton.cc \
	$(srcdir)/src/codegen/translate.cc \
	$(srcdir)/src/dfa/encoding/enc.cc \
	$(srcdir)/src/dfa/encoding/range_suffix.cc \
	$(srcdir)/src/dfa/encoding/utf16/utf16.cc \
	$(srcdir)/src/dfa/encoding/utf16/utf16_range.cc \
	$(srcdir)/src/dfa/encoding/utf16/utf16_regexp.cc \
	$(srcdir)/src/dfa/encoding/utf8/utf8.cc \
	$(srcdir)/src/dfa/encoding/utf8/utf8_range.cc \
	$(srcdir)/src/dfa/encoding/utf8/utf8_regexp.cc \
	$(srcdir)/src/dfa/actions.cc \
	$(srcdir)/src/dfa/dfa.cc \
	$(srcdir)/src/main.cc \
	$(srcdir)/src/mbo_getopt.cc \
	$(srcdir)/src/parse/input.cc \
	$(srcdir)/src/parse/scanner.cc \
	$(srcdir)/src/util/range.cc \
	$(srcdir)/src/util/substr.cc
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
