//go:generate re2go $INPUT -o $OUTPUT 
package main

func Lex(str string) int {
	var cursor, marker int

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	end = [\x00];

	* {
		return -1
	}

	"a" {
		return 1
	}

	"abc" {
		return 2
	}

	"abcde" {
		return 3
	}

	"abcdefg" {
		return 4
	}
	*/
}

func main() {
	if Lex("\000") != -1 {
		panic("expected error")
	}
	if Lex("a\000") != 1 {
		panic("expected 'a'")
	}
	if Lex("abc\000") != 2 {
		panic("expected 'abc'")
	}
	if Lex("abcde\000") != 3 {
		panic("expected 'abcde'")
	}
	if Lex("abcdefg\000") != 4 {
		panic("expected 'abcdefg'")
	}
}
