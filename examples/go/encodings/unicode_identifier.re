//go:generate re2go $INPUT -o $OUTPUT -8si --api simple
package main

/*!include:re2c "unicode_categories.re" */

func lex(yyinput string) int {
	var yycursor, yymarker int
	/*!re2c
		re2c:yyfill:enable = 0;
		re2c:YYCTYPE = byte;

		// Simplified "Unicode Identifier and Pattern Syntax"
		// (see https://unicode.org/reports/tr31)
		id_start    = L | Nl | [$_];
		id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
		identifier  = id_start id_continue*;

		identifier { return 0 }
		*          { return 1 }
	*/
}

func main() {
	if lex("_Ыдентификатор\000") != 0 {
		panic("error")
	}
}
