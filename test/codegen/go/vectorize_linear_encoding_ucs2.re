//go:generate re2go $INPUT -o $OUTPUT -i -w --vectorize-linear -Wno-vectorize-linear-disabled
package main

import "fmt"

func lex(yyinput []uint16) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!re2c
		re2c:api = simple;
		re2c:YYCTYPE = uint16;
		re2c:yyfill:enable = 0;
		"abcdefgh" { return 1, yycursor }
		*          { return 0, yycursor }
	*/
}

func main() {
	for pos := -1; pos < 7; pos++ {
		input := []uint16{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 0}
		if pos >= 0 {
			// The high byte overlaps the next character in a packed OR comparison.
			input[pos] |= input[pos+1] << 8
		}
		wantRule, wantLength := 0, 1
		if pos < 0 {
			wantRule, wantLength = 1, 8
		}
		rule, length := lex(input)
		if rule != wantRule || length != wantLength {
			panic(fmt.Sprintf("position %d: rule %d, length %d; expected %d, %d",
				pos, rule, length, wantRule, wantLength))
		}
	}
}
