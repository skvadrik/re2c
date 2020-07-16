//go:generate re2go $INPUT -o $OUTPUT
package main

import "testing"

// expect a null-terminated string
func lex(str string) int {
	var cursor int
	count := 0
loop:
	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";

	*      { return -1 }
	[\x00] { return count }
	[a-z]+ { count += 1; goto loop }
	[ ]+   { goto loop }
	*/
}

func TestLex(t *testing.T) {
	var tests = []struct {
		res int
		str string
	}{
		{0, "\000"},
		{3, "one two three\000"},
		{-1, "f0ur\000"},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			res := lex(x.str)
			if res != x.res {
				t.Errorf("got %d, want %d", res, x.res)
			}
		})
	}
}
