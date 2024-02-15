//go:generate re2go $INPUT -o $OUTPUT --recursive-functions -i
package main

// expect a null-terminated string
/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYFN = ["lex;int", "str;string", "cur;int", "count;int"];
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cur]";
	re2c:define:YYSKIP = "cur += 1";

	*      { return -1 }
	[\x00] { return count }
	[a-z]+ { count += 1; return lex(str, cur, count) }
	[ ]+   { return lex(str, cur, count) }
*/

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("\000", 0, 0), 0)
	assert_eq(lex("one two three\000", 0, 0), 3)
	assert_eq(lex("f0ur\000", 0, 0), -1)
}
