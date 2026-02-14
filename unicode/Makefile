all: unicode_categories.re

GEN := unicode_categories.re unicode_blocks.re
INPUT := UnicodeData.txt Blocks.txt

$(GEN): $(INPUT) generate
	./generate

# TODO: replace with the latest data: https://unicode.org/Public/UCD/latest/ucd/...
UnicodeData.txt:
	wget https://unicode.org/Public/15.1.0/ucd/UnicodeData.txt
Blocks.txt:
	wget https://unicode.org/Public/15.1.0/ucd/Blocks.txt

generate: generate.cc
	c++ generate.cc -o generate -O2 -g -Wall -Wextra

generate.cc: generate.re
	re2c -W generate.re -o generate.cc

clean:
	rm -f $(GEN) $(INPUT) generate generate.cc

install: $(GEN)
	mv unicode_categories.re ../include/unicode_categories.re
	mv unicode_blocks.re ../include/unicode_blocks.re
