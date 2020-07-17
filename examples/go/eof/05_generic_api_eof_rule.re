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
	var cursor, marker int
	limit := len(str)
	count := 0
loop:
	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:eof = 0;
	re2c:define:YYCTYPE    = byte;
	re2c:define:YYLESSTHAN = "cursor >= limit";
	re2c:define:YYPEEK     = "peek(str, cursor, limit)";
	re2c:define:YYSKIP     = "cursor += 1";
	re2c:define:YYBACKUP   = "marker = cursor";
	re2c:define:YYRESTORE  = "cursor = marker";

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
		{0, ""},
		{3, "'qu\000tes' 'are' 'fine: \\'' "},
		{-1, "'unterminated\\'"},
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
