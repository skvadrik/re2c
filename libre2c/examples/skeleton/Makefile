COPTS=-g -Wall -Werror

CSRC+=$(wildcard ../../libre2c/*.c)
CHDR+=$(wildcard ../../libre2c/*.h)


all: scanner

# the perl command removes the #line directives because they
# get in the way of source-level debuggers.
%.c: %.re
	re2c $(REOPTS) $< > $@
	perl -pi -e 's/^\#line.*$$//' $@


scanner: scanner.c main.c $(CHDR)
	$(CC) -I ../.. $(COPTS) -o $@ $(CSRC) scanner.c main.c

clean:
	rm -f scanner scanner.c
