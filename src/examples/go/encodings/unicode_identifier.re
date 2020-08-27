//go:generate re2go $INPUT -o $OUTPUT -8 -s -i
//
// Simplified "Unicode Identifier and Pattern Syntax"
// (see https://unicode.org/reports/tr31)

package main

import "testing"

/*!include:re2c "unicode_categories.re" */

func lex(str string) int {
	var cursor, marker int
	/*!re2c
	re2c:yyfill:enable    = 0;
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	id_start    = L | Nl | [$_];
	id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
	identifier  = id_start id_continue*;

	identifier { return 0 }
	*          { return 1 }
	*/
}

func TestLex(t *testing.T) {
	if lex("_Ыдентификатор\000") != 0 {
		t.Errorf("failed")
	}
}
