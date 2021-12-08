//go:generate re2go $INPUT -o $OUTPUT -i
package main

/*!include:re2c "definitions.go" */

func lex(str string) int {
	var cursor, marker int
	/*!re2c
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";
	re2c:yyfill:enable    = 0;

	number { return ResultOk }
	!include "extra_rules.re.inc";
	* { return ResultFail }
	*/
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("123\000"), ResultOk)
	assert_eq(lex("123.4567\000"), ResultOk)
}
