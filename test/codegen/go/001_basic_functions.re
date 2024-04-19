//go:generate re2go $INPUT -o $OUTPUT -d
package main

import "fmt"

type YYCTYPE byte

func Lex(str string) int {
	data := []YYCTYPE(str)
	var cursor, marker int

	YYPEEK := func() YYCTYPE { return data[cursor] }
	YYSKIP := func() { cursor++ }
	YYBACKUP := func() { marker = cursor }
	YYRESTORE := func() { cursor = marker }
	YYDEBUG := func() { fmt.Printf("Lex: char '%c'\n", data[cursor]); }

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:api:style = functions;

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
