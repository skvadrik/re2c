# $Id$

BIN = /usr/local/bin
MAN = /usr/local/man
RE2C_VERSION = 0.9.2

%.o : %.cc ; $(CC) -o $@ $(CFLAGS) -c $<
%.cc : %.y ; $(YACC)  $(YFLAGS) $<; mv $(YTAB).c $@

%.cc:	%.re
	-@if test -x re2c; then \
		echo "re2c -s $< >$@"; \
		re2c -s $< >$@; \
	else \
		echo "cp -f bootstrap/$@ $@"; \
		cp -f bootstrap/$@ $@; \
	fi

SOURCES	= code.cc dfa.cc main.cc parser.y actions.cc scanner.re substr.cc\
	translate.cc
OBJS	= code.o dfa.o main.o parser.o actions.o scanner.o substr.o\
	translate.o

CC			= g++
CFLAGS		= -O2 -Wall -I. -Wno-unused -Wno-parentheses -Wno-deprecated
YACC		= bison -y
YFLAGS		= -d
LDFLAGS		= 

default:	re2c

dist-clean:
	rm -f *.o *.s y.tab.c y.tab.h parser.cc .version version.h

clean:	dist-clean
	rm -f re2c scanner.cc README re2c.1 re2c.ps re2c*.spec makerpm

parser.cc:	parser.y
	$(YACC) $(YFLAGS) parser.y
	mv -f y.tab.c parser.cc

re2c:	README re2c.1 $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) -lstdc++

re2c.ps:
	gunzip -c doc/loplas.ps.gz > re2c.ps

.version:
	echo $(RE2C_VERSION) > .version

version.h:
	echo "#define RE2C_VERSION \"$(RE2C_VERSION)\"" > version.h

README:
	cat README.in | sed 's/RE2C_VERSION/$(RE2C_VERSION)/g' > README

makerpm:
	cat makerpm.in | sed 's/RE2C_VERSION/$(RE2C_VERSION)/g' > makerpm
	chmod +x makerpm

re2c.1:
	cat re2c.1.in | sed 's/RE2C_VERSION/$(RE2C_VERSION)/g' > re2c.1

install: re2c re2c.1
	install -d $(BIN)
	install -s re2c $(BIN)
	install -d $(MAN)/man1
	install -m 0644 re2c.1 $(MAN)/man1

uninstall:
	rm -f $(BIN)/re2c
	rm -f $(MAN)/man1/re2c.1*

dist: re2c scanner.cc
	mkdir re2c-$(RE2C_VERSION)
	cp -P `p4 files ... | sed s/\\\\/\\\\/depot\\\\/home\\\\/re2c\\\\/// | sed '/- delete/d' | sed s/#.*$$//` re2c-$(RE2C_VERSION)/
	tar zcf re2c-$(RE2C_VERSION).tar.gz re2c-$(RE2C_VERSION)/
	rm -rf re2c-$(RE2C_VERSION)

#
# generated with "gcc -I. -MM -x c++ *.cc *.y *.re"
# and edited by hand
#
actions.o : actions.cc globals.h basics.h parser.h scanner.h \
  token.h substr.h re.h ins.h dfa.h 
code.o : code.cc substr.h basics.h globals.h dfa.h re.h token.h \
  ins.h 
dfa.o : dfa.cc globals.h basics.h substr.h dfa.h re.h token.h \
  ins.h 
main.o : main.cc globals.h basics.h parser.h scanner.h token.h \
  substr.h re.h ins.h dfa.h version.h
substr.o : substr.cc substr.h basics.h 
translate.o : translate.cc globals.h basics.h 
scanner.o : scanner.re scanner.h token.h substr.h basics.h \
  parser.h re.h ins.h ./parser.o
parser.o : parser.y globals.h basics.h parser.h scanner.h token.h \
  substr.h re.h ins.h  version.h
