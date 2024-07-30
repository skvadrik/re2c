//go:generate re2go $INPUT -o $OUTPUT
package main

func Lex(yyinput string) int {
	var yycursor, yymarker int

	/*!re2c
	re2c:api = simple;
	re2c:yyfill:enable = 0;
	re2c:yych:conversion = 1;
	re2c:define:YYCTYPE = int8; // signed 8-bit

	end = [\x00];

	* {
		return -1
	}

	[0-9]+ end {
		return 1
	}
	*/
}

func main() {
	if Lex("123\000") != 1 {
		panic("expected 123")
	}
}
