//go:generate re2go $INPUT -o $OUTPUT -i --api simple
package main

/*!include:re2c "definitions.go" */

func lex(yyinput string) int {
	var yycursor, yymarker int
	/*!re2c
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;

		*      { return ResultFail }
		number { return ResultOk }
		!include "extra_rules.re.inc";
	*/
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("123\000"), ResultOk)
	assert_eq(lex("123.4567\000"), ResultOk)
}
