# Makefile
# Scott Bronson
# 27 Dec 2004

VERSION=0.7

COPTS=-g -Wall -Werror

CSRC+=$(wildcard re2c/*.c)
CHDR+=$(wildcard re2c/*.h)

all: examples
	$(MAKE) -C test

examples:
	$(MAKE) -C examples

test:
	$(MAKE) -C test test

clean:
	rm -f numscan tags
	$(MAKE) -C examples clean
	$(MAKE) -C test clean

distclean: clean
	rm -rf docs

# need to make clean before making docs.
# otherwise doxygen will parse .c and .re files and get very confused.
docs:
	$(MAKE) clean
	doxygen
	perl -pi -e "s/VERSION/$(VERSION)/" docs/html/index.html

release: distclean
	if find . | egrep "~|/\\."; then echo "INVISIBLE OR BAD FILES!  Won't finish." && exit 1; else exit 0; fi
	rm -rf /tmp/libre2c-$(VERSION) /tmp/libre2c-docs-$(VERSION)
	cp -r . /tmp/libre2c-$(VERSION)
	perl -pi -e "s/VERSION/$(VERSION)/" /tmp/libre2c-$(VERSION)/re2c/*
	(cd /tmp && tar zcf libre2c-$(VERSION).tar.gz libre2c-$(VERSION))
	(cd /tmp/libre2c-$(VERSION) && make docs && mv docs/html ../libre2c-docs-$(VERSION) && rmdir docs)

tags:
	ctags -R

.PHONY: docs clean distclean examples test release
