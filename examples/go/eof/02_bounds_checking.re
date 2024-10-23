//go:generate re2go $INPUT -o $OUTPUT --api simple
package main

import "strings"

/*!max:re2c*/

// Expects YYMAXFILL-padded string.
func lex(str string) int {
	// Pad string with YYMAXFILL zeroes at the end.
	yyinput := str + strings.Repeat("\000", int(YYMAXFILL))

	yycursor := 0
	yylimit := len(yyinput)
	count := 0

	for { /*!re2c
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "return -1";

		str = ['] ([^'\\] | [\\][^])* ['];

		[\x00] {
			// Check that it is the sentinel, not some unexpected null.
			if yycursor - 1 == len(str) { return count } else { return -1 }
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
