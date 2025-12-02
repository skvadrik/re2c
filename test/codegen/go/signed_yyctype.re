//go:generate re2go $INPUT -o $OUTPUT -i --api simple
package main

// In Go, comparison of int8 to a literal that doesn't fit into int8 limits
// (e.g. `yych >= 0xFF`) is a compile-time error. So this example won't compile
// (unlike C where it compiles, and the resulting lexer works incorrectly).

/*!rules:re2c
	re2c:yyfill:enable = 0;

	[\xff] { return 0 }
	*      { return 1 }
*/

func lex_unsigned(yyinput string) int {
	var yycursor int
	/*!use:re2c
		re2c:YYCTYPE = byte;
	*/
}

func lex_signed(yyinput string) int {
	var yycursor int
	/*!use:re2c
		re2c:YYCTYPE = int8; // should be unsigned! compilation error
	*/
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex_unsigned("\xff\x00" ), 0)
	assert_eq(lex_signed("\xff\x00" ), 1) // compilation error
}
