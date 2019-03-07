COPTS=-g -Wall -Werror

CSRC+=$(wildcard ../../libre2c/*.c)
CHDR+=$(wildcard ../../libre2c/*.h)


all: modnumscan

# the perl command removes the #line directives because they
# get in the way of source-level debuggers.
%.c: %.re
	re2c $(REOPTS) $< > $@
	perl -pi -e 's/^\#line.*$$//' $@


modnumscan: modnumscanner.c modnumparser.c $(CHDR)
	$(CC) -I ../.. $(COPTS) -o $@ $(CSRC) modnumscanner.c modnumparser.c

clean:
	rm -f modnumscan modnumscanner.c
