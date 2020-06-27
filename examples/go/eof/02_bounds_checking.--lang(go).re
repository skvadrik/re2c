//go:generate "${RE2C}" --lang go "${GOFILE}" -o example_test.go
package main

import (
	"strings"
	"testing"
)

/*!max:re2c*/

// Expects YYMAXFILL-padded string.
func lex(str string) int {
	var cursor int
	limit := len(str)
	count := 0
loop:
	/*!re2c
	re2c:define:YYCTYPE    = byte;
	re2c:define:YYPEEK     = "str[cursor]";
	re2c:define:YYSKIP     = "cursor += 1";
	re2c:define:YYLESSTHAN = "limit - cursor < @@{len}";
	re2c:define:YYFILL     = "return -1";

	*                           { return -1 }
	[\x00]                      { return count }
	['] ([^'\\] | [\\][^])* ['] { count += 1; goto loop }
	[ ]+                        { goto loop }
	*/
}

// Pad string with YYMAXFILL zeroes at the end.
func pad(str string) string {
	return str + strings.Repeat("\000", YYMAXFILL)
}

func TestLex(t *testing.T) {
	var tests = []struct {
		res int
		str string
	}{
		{0, ""},
		{3, "'qu\000tes' 'are' 'fine: \\'' "},
		{-1, "'unterminated\\'"},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			res := lex(pad(x.str))
			if res != x.res {
				t.Errorf("got %d, want %d", res, x.res)
			}
		})
	}
}
