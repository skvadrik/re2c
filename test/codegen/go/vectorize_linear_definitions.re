//go:generate re2go $INPUT -o $OUTPUT -i --vectorize-linear -Werror
package main

// A definitions-only block keeps the default generic API and character type.
/*!re2c
	word = [a-z]+;
*/

func lex(yyinput string) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!re2c
		re2c:api = simple;
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;
		"content-length" { return 2, yycursor }
		word             { return 1, yycursor }
		*                { return 0, yycursor }
	*/
}

func main() {
	for _, tc := range []struct {
		input string
		rule, cursor int
	}{
		{"content-length\x00", 2, 14},
		{"abc\x00", 1, 3},
		{"!\x00", 0, 1},
	} {
		if rule, cursor := lex(tc.input); rule != tc.rule || cursor != tc.cursor {
			panic(tc.input)
		}
	}
}
