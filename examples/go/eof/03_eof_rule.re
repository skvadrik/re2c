//go:generate re2go $INPUT -o $OUTPUT
package main

import "testing"

// Expects a null-terminated string.
func lex(str string) int {
	var cursor, marker int
	limit := len(str) - 1 // limit points at the terminating null
	count := 0
loop:
	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:eof = 0;
	re2c:define:YYCTYPE    = byte;
	re2c:define:YYPEEK     = "str[cursor]";
	re2c:define:YYSKIP     = "cursor += 1";
	re2c:define:YYBACKUP   = "marker = cursor";
	re2c:define:YYRESTORE  = "cursor = marker";
	re2c:define:YYLESSTHAN = "limit <= cursor";

	*                           { return -1 }
	$                           { return count }
	['] ([^'\\] | [\\][^])* ['] { count += 1; goto loop }
	[ ]+                        { goto loop }
	*/
}

func TestLex(t *testing.T) {
	var tests = []struct {
		res int
		str string
	}{
		{0, "\000"},
		{3, "'qu\000tes' 'are' 'fine: \\'' \000"},
		{-1, "'unterminated\\'\000"},
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
