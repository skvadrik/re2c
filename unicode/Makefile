all: unicode_categories.re

unicode_categories.re: UnicodeData.txt generate
	./generate

# TODO: replace with the latest UnicodeData.txt:
#       https://unicode.org/Public/UCD/latest/ucd/UnicodeData.txt
UnicodeData.txt:
	wget https://unicode.org/Public/15.1.0/ucd/UnicodeData.txt

generate: generate.cc
	c++ generate.cc -o generate -O2 -g -Wall -Wextra

generate.cc: generate.re
	re2c -W generate.re -o generate.cc

clean:
	rm -f \
		unicode_categories.re \
		generate \
		generate.cc \
		UnicodeData.txt

install: unicode_categories.re
	mv unicode_categories.re ../include/unicode_categories.re
