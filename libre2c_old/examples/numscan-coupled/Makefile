COPTS=-g -Wall -Werror

CSRC+=$(wildcard ../../libre2c/*.c)
CHDR+=$(wildcard ../../libre2c/*.h)


all: numscan

numscan.c: numscan.re
	re2c $(REOPTS) $< > $@
	perl -pi -e 's/^\#line.*$$//' $@

numscan: numscan.c $(CHDR)
	$(CC) -I ../.. $(COPTS) -o $@ $< $(CSRC)

clean:
	rm -f numscan.c numscan
