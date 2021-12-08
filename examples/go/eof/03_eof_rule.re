//go:generate re2go $INPUT -o $OUTPUT
package main

// Expects a null-terminated string.
func lex(str string) int {
	var cursor, marker int
	limit := len(str) - 1 // limit points at the terminating null
	count := 0

	for {/*!re2c
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
		['] ([^'\\] | [\\][^])* ['] { count += 1; continue }
		[ ]+                        { continue }
	*/}
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("\000"), 0)
	assert_eq(lex("'qu\000tes' 'are' 'fine: \\'' \000"), 3)
	assert_eq(lex("'unterminated\\'\000"), -1)
}
