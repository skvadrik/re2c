GEN := unicode_categories.re unicode_blocks.re unicode_properties.re
INPUT := UnicodeData.txt Blocks.txt PropList.txt

all: $(GEN)

$(GEN): $(INPUT) generate
	./generate

UnicodeData.txt:
	wget https://unicode.org/Public/UCD/latest/ucd/UnicodeData.txt
Blocks.txt:
	wget https://unicode.org/Public/UCD/latest/ucd/Blocks.txt
PropList.txt:
	wget https://unicode.org/Public/UCD/latest/ucd/PropList.txt

generate: generate.cc
	c++ generate.cc -o generate -O2 -g -Wall -Wextra

generate.cc: generate.re
	re2c -W generate.re -o generate.cc

clean:
	rm -f $(GEN) $(INPUT) generate generate.cc

install: $(GEN)
	mv unicode_categories.re ../include/unicode_categories.re
	mv unicode_blocks.re ../include/unicode_blocks.re
	mv unicode_blocks_{8,x,u}_encoding_policy_{ignore,substitute,fail}.re ../test/encodings
	mv unicode_group_*_{8,x,u}.re ../test/encodings
	mv unicode_properties.re ../include/unicode_properties.re
