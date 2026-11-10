//go:generate re2go $INPUT -o $OUTPUT
package main

func lex(yyinput string) int {
	var yycursor, yymarker uint

	/*!re2c
	re2c:api = simple;
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:YYPTYPE = uint;
	re2c:yyshift:conversion = 1;

	"a" / "bc" { return int(yycursor) }
	*          { return -1 }
	*/
}

func main() {
	if lex("abc\000") != 1 {
		panic("expected 1")
	}
	if lex("abd\000") != -1 {
		panic("expected -1")
	}
}
