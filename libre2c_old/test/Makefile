CSRC+=$(wildcard ../libre2c/*.c)
CHDR+=$(wildcard ../libre2c/*.h)

COPTS=-Wall -Werror -g
CMPLOC=../examples/compare

all: tester

tester: zutest.c zutest.h retest.c retest.h tester.c $(CSRC) $(CHDR) $(CMPLOC)/compare.c $(CMPLOC)/compare.h
	gcc $(COPTS) -I. -I.. -I$(CMPLOC) zutest.c retest.c tester.c $(CMPLOC)/compare.c $(CSRC) $(CHDR) -DZUTEST -o tester

test: tester
	./tester

clean:
	rm -f tester
