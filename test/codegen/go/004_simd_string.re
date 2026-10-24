//go:generate re2go --vectorize-loops $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
	"strings"
	"unsafe"
)

func lexSimd(yyinput string, yycursor int) (int, int) {
	// This view keeps the string data alive and must never be written to.
	input := unsafe.Slice(unsafe.StringData(yyinput), len(yyinput))
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYINPUT = input;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2, yycursor";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	[a-z]+ { return 1, yycursor }
	*      { return -1, yycursor }
	*/
}

func lexSimdUint(yyinput string, yycursor uint) (int, uint) {
	input := unsafe.Slice(unsafe.StringData(yyinput), len(yyinput))
	yylimit := uint(len(yyinput))
	/*!re2c
	re2c:api = simple;
	re2c:YYINPUT = input;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2, yycursor";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	[a-z]+ { return 1, yycursor }
	*      { return -1, yycursor }
	*/
}

func lexScalar(yyinput string, yycursor int) (int, int) {
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYINPUT = yyinput;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2, yycursor";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;
	[a-z]+ { return 1, yycursor }
	*      { return -1, yycursor }
	*/
}

func main() {
	// Include read-only static storage and the empty-string StringData case.
	const literal = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl!"
	if kind, end := lexSimd(literal, 0); kind != 1 || end != len(literal)-1 {
		panic("literal input mismatch")
	}
	if kind, end := lexSimdUint(literal, 0); kind != 1 || end != uint(len(literal)-1) {
		panic("uint literal input mismatch")
	}
	for _, data := range []string{"", "a", literal} {
		if kind, end := lexSimd(data, len(data)); kind != -2 || end != len(data) {
			panic("empty input mismatch")
		}
		if kind, end := lexSimdUint(data, uint(len(data))); kind != -2 || end != uint(len(data)) {
			panic("uint empty input mismatch")
		}
	}
	checked := 0
	for offset := 0; offset < 32; offset++ {
		for n := 0; n <= 160; n++ {
			for _, stop := range []byte{0, ' ', '`', '{', 0x80, 0xff} {
				for _, padding := range []int{0, 64} {
					data := strings.Repeat("!", offset) + strings.Repeat("a", n) + string([]byte{stop}) + strings.Repeat("!", padding)
					t1, c1 := lexSimd(data, offset)
					t2, c2 := lexScalar(data, offset)
					t3, c3 := lexSimdUint(data, uint(offset))
					want, end := 1, offset+n
					if n == 0 { want, end = -1, offset+1 }
					if t1 != want || t2 != want || c1 != end || c2 != end {
						panic(fmt.Sprintf("offset=%d n=%d stop=%02x padding=%d: simd=(%d,%d) scalar=(%d,%d), want=(%d,%d)", offset, n, stop, padding, t1, c1, t2, c2, want, end))
					}
					if t3 != want || c3 != uint(end) {
						panic(fmt.Sprintf("offset=%d n=%d stop=%02x padding=%d: uint=(%d,%d), want=(%d,%d)", offset, n, stop, padding, t3, c3, want, end))
					}
					checked++
				}
			}
		}
	}
	fmt.Printf("OK: %d string inputs bit-exact with int and uint cursors\n", checked)
}
