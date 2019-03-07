COPTS=-g -Wall -Werror

CSRC+=$(wildcard ../../libre2c/*.c)
CHDR+=$(wildcard ../../libre2c/*.h)


all: comments

# the perl command removes the #line directives because they
# get in the way of source-level debuggers.
%.c: %.re
	re2c $(REOPTS) $< > $@
	perl -pi -e 's/^\#line.*$$//' $@

comments: cscan.c cparse.c $(CHDR)
	$(CC) -I ../.. $(COPTS) -o $@ $(CSRC) cscan.c cparse.c

clean:
	rm -f comments cscan.c
