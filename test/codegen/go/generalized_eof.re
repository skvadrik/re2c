//go:generate re2go $INPUT -o $OUTPUT --api simple -i
package main

import "strings"

/*!rules:re2c:x
	re2c:YYCTYPE = byte;
	re2c:api:style = free-form;

	$           { return 0 }
	*           { return 1 }
	[a] $       { return 2 }
	[a]         { return 3 }
	[b] $ | [b] { return 4 }
	[c]+ $      { return 5 }
*/

func lex_simple(yyinput string) int {
	yycursor := 0
	yymarker := 0
	yylimit := len(yyinput)

	/*!use:re2c:x
		re2c:yyfill:enable = 0;
	*/
}

func lex_eof(str string) int {
	yyinput := str + "\000"
	yycursor := 0
	yymarker := 0
	yylimit := len(str)

	/*!use:re2c:x
		re2c:eof = 0;
		re2c:YYFILL = "false"; // always fails
		re2c:YYEND = "yycursor == yylimit";
	*/
}

/*!max:re2c*/

func lex_scc(str string) int {
	yyinput := str + strings.Repeat("\000", int(YYMAXFILL))
	yycursor := 0
	yymarker := 0
	yylimit := len(yyinput)
	end := len(str)

	/*!use:re2c:x
		re2c:YYFILL = "return -1"; // always fails
		re2c:YYEND = "yycursor == end";
	*/
}

func test(str string, ret int) {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex_simple(str), ret)
	assert_eq(lex_eof(str), ret)
	assert_eq(lex_scc(str), ret)
}

func main() {
	test("", 0)
	test("a", 2)
	test("ax", 3)
	test("b", 4)
	test("bx", 4)
	test("ccc", 5)
}
