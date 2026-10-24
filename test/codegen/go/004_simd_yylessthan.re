//go:generate re2go --vectorize-loops --syntax 004_simd_yylessthan.inc $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
)

var (
	input  []byte
	cursor int
	limit  int
)

// Calls of the user-defined length check, and those made by the vector loop (the only check
// that needs more than one vector of input).
var guards, vectorGuards int

func lessThan(need int) bool {
	guards++
	if need > 32 {
		vectorGuards++
	}
	return limit-cursor < need
}

func lexSimd() int {
	/*!re2c
	re2c:vectorize:loops = 1;
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	[a-z]+ { return 1 }
	"\x00" { return 0 }
	*      { return -1 }
	*/
}

func lexScalar() int {
	/*!re2c
	re2c:vectorize:loops = 0;
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	[a-z]+ { return 1 }
	"\x00" { return 0 }
	*      { return -1 }
	*/
}

func lex(fn func() int, data []byte) (int, int) {
	input, cursor, limit = data, 0, len(data)
	return fn(), cursor
}

func main() {
	for n := 1; n <= 200; n++ {
		// A run of letters, a space, then a null terminator.
		data := make([]byte, n+2)
		for i := 0; i < n; i++ {
			data[i] = 'a' + byte(i%26)
		}
		data[n] = ' '
		t1, c1 := lex(lexSimd, data)
		t2, c2 := lex(lexScalar, data)
		if t1 != 1 || t2 != 1 || c1 != n || c2 != n {
			panic(fmt.Sprintf("n=%d: simd=(%d,%d) scalar=(%d,%d)", n, t1, c1, t2, c2))
		}
	}
	// The vector loop is entered for runs longer than the guard, so it must have called the
	// user-defined check.
	if vectorGuards == 0 {
		panic("the vector loop does not use code:yylessthan")
	}
	fmt.Printf("OK: %d checks, %d in the vector loop\n", guards, vectorGuards)
}
