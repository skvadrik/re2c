# $Log$
# Revision 1.1  2003/12/13 04:58:19  nuffer
# Initial revision
#
#Revision 1.1  1994/04/08  16:30:37  peter
#Initial revision
#

BIN = /usr/local/bin
MAN = /usr/local/man

%.o : %.cc ; $(CC) -o $@ $(CFLAGS) -c $<
%.cc : %.y ; $(YACC)  $(YFLAGS) $<; mv $(YTAB).c $@
%.cc : %.l ; $(LEX)   $(LFLAGS) $<; mv $(LEXYY).c $@

%.cc:	%.re
	re2c -s $< >$@

SOURCES	= code.cc dfa.cc main.cc parser.y actions.cc scanner.re substr.cc\
	translate.cc
OBJS	= code.o dfa.o main.o parser.o actions.o scanner.o substr.o\
	translate.o

CC		= g++
CFLAGS		= -O2 -Wall -I. -Wno-unused -Wno-parentheses
YFLAGS		= -d
LDFLAGS		= 

default:	re2c

clean:
	rm -f *.o *.s y.tab.c y.tab.h scanner.cc parser.cc .version version.h re2c

parser.cc:	parser.y
	yacc -d parser.y
	mv -f y.tab.c parser.cc

re2c:	$(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) -lstdc++

.version: README
	egrep "^Version" README | sed 's/Version //' > .version

version.h: .version
	echo "#define RE2C_VERSION" `cat .version` > version.h

install: re2c
	install -d $(BIN)
	install -s re2c $(BIN)
	install -d $(MAN)/man1
	install -m 0644 re2c.1 $(MAN)/man1

dist: re2c scanner.cc .version
	mkdir re2c-`cat .version`
	cp -P `p4 files ... | sed s/\\\\/\\\\/depot\\\\/home\\\\/re2c\\\\/// | sed '/- delete/d' | sed s/#.*$$//` re2c-`cat .version`/
	tar zcf re2c-`cat .version`.tar.gz re2c-`cat .version`/
	rm -rf re2c-`cat .version`

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
  substr.h re.h ins.h 
