//go:generate re2go -c $INPUT -o $OUTPUT -i
package main

import "testing"
/*!include:re2c "definitions.go" */

func lex(str string) int {
	var cursor int
	/*!re2c
	re2c:yyfill:enable  = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK  = "str[cursor]";
	re2c:define:YYSKIP  = "cursor += 1";

	number { return ResultOk }
	*      { return ResultFail }
	*/
}

func TestLex(t *testing.T) {
	if lex("123\000") != ResultOk {
		t.Errorf("error")
	}
}
