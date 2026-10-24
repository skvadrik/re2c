//go:generate re2go --vectorize-loops -Wno-unreachable-rules --syntax 004_simd_xrange.inc $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
	"strings"
)

var (
	input  []byte
	cursor int
	limit  int
)

// String body: the complement consists of single code units only (0x00, '\n', '"', '\\').
func lexString() int {
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	[^"\\\x00\n]+ { return 1 }
	*             { return -1 }
	*/
}

// Identifier tail: the complement mixes ranges and a single code unit ('`').
func lexIdent() int {
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	[a-zA-Z_][a-zA-Z0-9_]* { return 2 }
	*                      { return -1 }
	*/
}

// Any byte: the complement is empty, so the `xrange` list renders nothing. The loop only ends at
// the end of input, so the action of the first rule is unreachable (-Wno-unreachable-rules); the
// leading "a" makes the lexer read the current code unit, so that `yych` is used.
func lexAny() int {
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	"a" [\x00-\xff]* { return 3 }
	*                { return -1 }
	*/
}

func main() {
	checked := 0
	for n := 0; n <= 160; n++ {
		for b := 0; b < 256; b++ {
			for _, tc := range []struct {
				lex func() int
				kind int
				accept bool
			}{
				{lexString, 1, b != 0 && b != '\n' && b != '"' && b != '\\'},
				{lexIdent, 2, b >= 'a' && b <= 'z' || b >= 'A' && b <= 'Z' || b == '_' || n > 0 && b >= '0' && b <= '9'},
			} {
				input = append([]byte(strings.Repeat("a", n)), byte(b))
				input = append(input, make([]byte, 65)...)
				cursor, limit = 0, len(input)
				want, end := tc.kind, n
				if tc.accept { end++ } else if n == 0 { want, end = -1, 1 }
				got := tc.lex()
				if got != want || cursor != end {
					panic(fmt.Sprintf("kind=%d n=%d byte=%02x: got=(%d,%d) want=(%d,%d)", tc.kind, n, b, got, cursor, want, end))
				}
				checked++
			}
		}
		input = make([]byte, n)
		for i := range input { input[i] = byte(i*37) }
		if n > 0 { input[0] = 'a' }
		cursor, limit = 0, len(input)
		if got := lexAny(); got != -2 || cursor != n {
			panic(fmt.Sprintf("any n=%d: got=(%d,%d)", n, got, cursor))
		}
		checked++
	}
	fmt.Printf("OK: %d complement inputs checked\n", checked)
}
