//go:generate re2go $INPUT -o $OUTPUT
package main

import "testing"

// Returns "fake" terminating null if cursor has reached limit.
func peek(str string, cursor int, limit int) byte {
	if cursor >= limit {
		return 0 // fake null
	} else {
		return str[cursor]
	}
}

// Expects a string without terminating null.
func lex(str string) int {
	var cursor int
	limit := len(str)
	count := 0
loop:
	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE    = byte;
	re2c:define:YYLESSTHAN = "cursor >= limit";
	re2c:define:YYPEEK     = "peek(str, cursor, limit)";
	re2c:define:YYSKIP     = "cursor += 1";

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
		{0, ""},
		{3, "one two three"},
		{-1, "f0ur"},
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
