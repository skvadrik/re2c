//go:generate re2go $INPUT -o $OUTPUT
package main

import "strings"

/*!max:re2c*/

// Expects YYMAXFILL-padded string.
func lex(str string) int {
	// Pad string with YYMAXFILL zeroes at the end.
	buf := str + strings.Repeat("\000", YYMAXFILL)

	var cur int
	lim := len(buf)
	count := 0

	for { /*!re2c
		re2c:define:YYCTYPE    = byte;
		re2c:define:YYPEEK     = "buf[cur]";
		re2c:define:YYSKIP     = "cur += 1";
		re2c:define:YYLESSTHAN = "lim - cur < @@";
		re2c:define:YYFILL     = "return -1";

		str = ['] ([^'\\] | [\\][^])* ['];

		[\x00] {
			// Check that it is the sentinel, not some unexpected null.
			if cur - 1 == len(str) { return count } else { return -1 }
		}
		str  { count += 1; continue }
		[ ]+ { continue }
		*    { return -1 }
	*/
	}
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex(""), 0)
	assert_eq(lex("'qu\000tes' 'are' 'fine: \\'' "), 3)
	assert_eq(lex("'unterminated\\'"), -1)
	assert_eq(lex("'unexpected \000 null\\'"), -1)
}
