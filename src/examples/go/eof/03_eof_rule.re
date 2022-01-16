//go:generate re2go $INPUT -o $OUTPUT
package main

// Expects a null-terminated string.
func lex(str string) int {
	var cur, mar int
	lim := len(str) - 1 // lim points at the terminating null
	count := 0

	for { /*!re2c
		re2c:eof = 0;
		re2c:define:YYCTYPE    = byte;
		re2c:define:YYPEEK     = "str[cur]";
		re2c:define:YYSKIP     = "cur += 1";
		re2c:define:YYBACKUP   = "mar = cur";
		re2c:define:YYRESTORE  = "cur = mar";
		re2c:define:YYLESSTHAN = "lim <= cur";
		re2c:yyfill:enable = 0;

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
