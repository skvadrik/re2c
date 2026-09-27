//go:generate re2go --vectorize-loops -Wno-unreachable-rules $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
)

// The vector loop below does not use math/bits, as its class has no exits.
var _ = bits.TrailingZeros32

var (
	input  []byte
	cursor int
	limit  int
)

// The loop class contains all code units, so its complement (the `xrange`
// list) is empty and the vector loop has no exit comparisons: it skips whole
// vectors while the length guard holds, and the scalar code handles the rest.
// The loop only ends at the end of input (YYFILL returns 1), so the action of
// the rule is unreachable; the test compares the final cursor positions.
func lexSimd() int {
	/*!re2c
	re2c:vectorize:loops = 1;
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYFILL = "return 1";
	re2c:YYFILL:naked = 1;

	"a" [\x00-\xff]* { return 2 }
	*                { return -1 }
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
	re2c:YYFILL = "return 1";
	re2c:YYFILL:naked = 1;

	"a" [\x00-\xff]* { return 2 }
	*                { return -1 }
	*/
}

func main() {
	checked := 0
	for n := 0; n <= 200; n++ {
		buf := make([]byte, n)
		for j := range buf {
			buf[j] = byte(j * 37)
		}
		if n > 0 {
			buf[0] = 'a'
		}
		input, cursor, limit = buf, 0, len(buf)
		t1, c1 := lexSimd(), cursor
		input, cursor, limit = buf, 0, len(buf)
		t2, c2 := lexScalar(), cursor
		if t1 != t2 || c1 != c2 {
			panic(fmt.Sprintf("mismatch on length %d: simd=(%d,%d) scalar=(%d,%d)", n, t1, c1, t2, c2))
		}
		checked++
	}
	fmt.Printf("OK: %d inputs bit-exact\n", checked)
}
