//go:generate re2go $INPUT -o $OUTPUT --vectorize-linear -Werror
package main

func lex(yyinput string) int {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!re2c
		re2c:api = simple;
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;
		"abcdefgh" { return 1 }
		*          { return 0 }
	*/
}
