//go:generate re2go $INPUT -o $OUTPUT --api simple
package main

// Expects a null-terminated string.
func lex(yyinput string) int {
	var yycursor, yymarker int
	yylimit := len(yyinput) - 1 // lim points at the terminating null
	count := 0

	for { /*!re2c
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;
		re2c:eof = 0;

		str = ['] ([^'\\] | [\\][^])* ['];

		*    { return -1 }
		$    { return count }
		str  { count += 1; continue }
		[ ]+ { continue }
	*/
	}
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("\000"), 0)
	assert_eq(lex("'qu\000tes' 'are' 'fine: \\'' \000"), 3)
	assert_eq(lex("'unterminated\\'\000"), -1)
}
