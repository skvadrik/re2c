//go:generate re2go $INPUT -o $OUTPUT -i
package main

/*!include:re2c "definitions.go" */

func lex(str string) int {
	var cur, mar int
	/*!re2c
		re2c:define:YYCTYPE   = byte;
		re2c:define:YYPEEK    = "str[cur]";
		re2c:define:YYSKIP    = "cur += 1";
		re2c:define:YYBACKUP  = "mar = cur";
		re2c:define:YYRESTORE = "cur = mar";
		re2c:yyfill:enable    = 0;

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
