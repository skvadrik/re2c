//go:generate re2go -c $INPUT -o $OUTPUT -i
package main

import "testing"
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

func TestLex(t *testing.T) {
	if lex("123\000") != ResultOk {
		t.Errorf("error")
	}
	if lex("123.4567\000") != ResultOk {
		t.Errorf("error")
	}
}
