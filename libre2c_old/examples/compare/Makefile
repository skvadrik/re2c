COPTS=-g -Wall -Werror

CSRC+=$(wildcard ../../libre2c/*.c)
CHDR+=$(wildcard ../../libre2c/*.h)


all: compare

# the perl command removes the #line directives because they
# get in the way of source-level debuggers.
%.c: %.re
	re2c $(REOPTS) $< > $@
	perl -pi -e 's/^\#line.*$$//' $@

compare: cmpmain.c compare.c compare.h $(CHDR)
	$(CC) -I../.. $(COPTS) -o $@ $(CSRC) cmpmain.c compare.c

clean:
	rm -f compare
