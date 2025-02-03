//go:generate re2go $INPUT -o $OUTPUT
package main

// Returns "fake" terminating null if cursor has reached limit.
func peek(str string, cur int) byte {
	if cur >= len(str) {
		return 0 // fake null
	} else {
		return str[cur]
	}
}

// Expects a string without terminating null.
func lex(str string) int {
	var cur int
	count := 0

	for { /*!re2c
		re2c:yyfill:enable = 0;
		re2c:YYCTYPE = byte;
		re2c:YYPEEK = "peek(str, cur)";
		re2c:YYSKIP = "cur += 1";

		*      { return -1 }
		[\x00] { return count }
		[a-z]+ { count += 1; continue }
		[ ]+   { continue }
	*/
	}
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex(""), 0)
	assert_eq(lex("one two three"), 3)
	assert_eq(lex("f0ur"), -1)
}
