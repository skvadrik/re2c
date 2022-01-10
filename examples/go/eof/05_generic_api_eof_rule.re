//go:generate re2go $INPUT -o $OUTPUT
package main

// Returns "fake" terminating null if cursor has reached limit.
func peek(str string, cur int, lim int) byte {
	if cur >= lim {
		return 0 // fake null
	} else {
		return str[cur]
	}
}

// Expects a string without terminating null.
func lex(str string) int {
	var cur, mar int
	lim := len(str)
	count := 0

	for { /*!re2c
		re2c:eof = 0;
		re2c:define:YYCTYPE    = byte;
		re2c:define:YYLESSTHAN = "cur >= lim";
		re2c:define:YYPEEK     = "peek(str, cur, lim)";
		re2c:define:YYSKIP     = "cur += 1";
		re2c:define:YYBACKUP   = "mar = cur";
		re2c:define:YYRESTORE  = "cur = mar";
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
	assert_eq(lex(""), 0)
	assert_eq(lex("'qu\000tes' 'are' 'fine: \\'' "), 3)
	assert_eq(lex("'unterminated\\'"), -1)
}
