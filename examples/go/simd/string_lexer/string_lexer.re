//go:generate re2go $INPUT -o $OUTPUT -i --api simple --vectorize-loops
//go:build goexperiment.simd && amd64

package main

// This example lexes a double-quoted string literal with JSON-like escapes.
// Both lexers below are generated from the same rules block: the only
// difference is that the scalar one disables loop vectorization, so they
// share the same DFA and differ only in the SIMD fast-forward preamble
// that `--vectorize-loops` emits for the reflexive loop on string bytes.
// See README.md in this directory for the benchmark.

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
)

/*!rules:re2c:str
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -1";
	re2c:YYFILL:naked = 1;

	*               { return -1 }
	"\""            { return yycursor - start - 1 }
	"\\"            {
		if yycursor >= yylimit { return -1 }
		switch yyinput[yycursor] {
		case '\\', '"', '/', 'b', 'f', 'n', 'r', 't':
			yycursor++
			continue
		}
		return -1
	}
	[^"\\\x00\n\r]+ { continue }
*/

// LexStringSIMD expects a double quote at the start of the input and returns
// the length of the string body (excluding quotes), or -1 on error.
func LexStringSIMD(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)

	if yycursor >= yylimit || yyinput[yycursor] != '"' {
		return -1
	}
	yycursor++
	start := yycursor

	for {
		/*!use:re2c:str
		re2c:vectorize:loops = 1;
		*/
	}
}

// LexStringScalar is the same lexer with loop vectorization disabled.
func LexStringScalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)

	if yycursor >= yylimit || yyinput[yycursor] != '"' {
		return -1
	}
	yycursor++
	start := yycursor

	for {
		/*!use:re2c:str
		re2c:vectorize:loops = 0;
		*/
	}
}

func main() {
	if !archsimd.X86.AVX2() {
		fmt.Println("AVX2 is not available, skipping")
		return
	}
	tests := []struct {
		str  string
		want int
	}{
		{`""`, 0},
		{`"short"`, 5},
		{`"a string that is long enough to take the vectorized path"`, 56},
		{`"escapes \" \\ \/ \b \f \n \r \t within a long enough string"`, 59},
		{`"bad escape \x in a string that is long enough"`, -1},
		{"\"newline \n inside a string that is long enough\"", -1},
		{`"unterminated string that is long enough to vectorize`, -1},
	}
	for _, t := range tests {
		s := []byte(t.str)
		if got := LexStringSIMD(s); got != t.want {
			panic(fmt.Sprintf("LexStringSIMD(%q) = %d, want %d", t.str, got, t.want))
		}
		if got := LexStringScalar(s); got != t.want {
			panic(fmt.Sprintf("LexStringScalar(%q) = %d, want %d", t.str, got, t.want))
		}
	}
}
