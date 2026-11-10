//go:generate re2go --arch x86 --vectorize-loops $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
)

type OpaqueGo struct {
	raw []byte
	pos int
	end int
	bak int
}

func lexGeneric16(st *OpaqueGo) int {
	/*!re2c
	re2c:api = generic;
	re2c:api:style = free-form;
	re2c:api:sigil = "@@";
	re2c:YYCTYPE = byte;
	re2c:YYPEEK = "st.raw[st.pos]";
	re2c:YYPEEK16 = "archsimd.LoadUint8x16(st.raw[st.pos : st.pos+16]).AsInt8x16()";
	re2c:YYSKIP = "st.pos++";
	re2c:YYBACKUP = "st.bak = st.pos";
	re2c:YYRESTORE = "st.pos = st.bak";
	re2c:YYSHIFT = "st.pos += @@";
	re2c:YYLESSTHAN = "(st.end - st.pos) < @@";
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:size = 16;

	[a-zA-Z_][a-zA-Z0-9_]* { return st.pos }
	*                      { return -1 }
	*/
}

func lexGeneric32(st *OpaqueGo) int {
	/*!re2c
	re2c:api = generic;
	re2c:api:style = free-form;
	re2c:api:sigil = "@@";
	re2c:YYCTYPE = byte;
	re2c:YYPEEK = "st.raw[st.pos]";
	re2c:YYPEEK32 = "archsimd.LoadUint8x32(st.raw[st.pos : st.pos+32]).AsInt8x32()";
	re2c:YYSKIP = "st.pos++";
	re2c:YYBACKUP = "st.bak = st.pos";
	re2c:YYRESTORE = "st.pos = st.bak";
	re2c:YYSHIFT = "st.pos += @@";
	re2c:YYLESSTHAN = "(st.end - st.pos) < @@";
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:size = 32;

	[a-zA-Z_][a-zA-Z0-9_]* { return st.pos }
	*                      { return -1 }
	*/
}

func lexSingletonScalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;

	[^x]+ { return yycursor }
	*     { return -1 }
	*/
}

func lexSingletonVec16(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 16;

	[^x]+ { return yycursor }
	*     { return -1 }
	*/
}

func lexSingletonVec32(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 32;

	[^x]+ { return yycursor }
	*     { return -1 }
	*/
}

func lex0To127Scalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;

	[\x80-\xff]+ { return yycursor }
	*            { return -1 }
	*/
}

func lex0To127Vec16(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 16;

	[\x80-\xff]+ { return yycursor }
	*            { return -1 }
	*/
}

func lex0To127Vec32(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 32;

	[\x80-\xff]+ { return yycursor }
	*            { return -1 }
	*/
}

func lex128To255Scalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;

	[\x00-\x7f]+ { return yycursor }
	*            { return -1 }
	*/
}

func lex128To255Vec16(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 16;

	[\x00-\x7f]+ { return yycursor }
	*            { return -1 }
	*/
}

func lex128To255Vec32(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 32;

	[\x00-\x7f]+ { return yycursor }
	*            { return -1 }
	*/
}

func lexInteriorScalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;

	[^a-z]+ { return yycursor }
	*       { return -1 }
	*/
}

func lexInteriorVec16(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 16;

	[^a-z]+ { return yycursor }
	*       { return -1 }
	*/
}

func lexInteriorVec32(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 32;

	[^a-z]+ { return yycursor }
	*       { return -1 }
	*/
}

func lexCross80Scalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;

	[^\x60-\x9f]+ { return yycursor }
	*             { return -1 }
	*/
}

func lexCross80Vec16(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 16;

	[^\x60-\x9f]+ { return yycursor }
	*             { return -1 }
	*/
}

func lexCross80Vec32(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 32;

	[^\x60-\x9f]+ { return yycursor }
	*             { return -1 }
	*/
}

func lexLo127Scalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;

	[\x00-\x1f\x80-\xff]+ { return yycursor }
	*                     { return -1 }
	*/
}

func lexLo127Vec16(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 16;

	[\x00-\x1f\x80-\xff]+ { return yycursor }
	*                     { return -1 }
	*/
}

func lexLo127Vec32(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 32;

	[\x00-\x1f\x80-\xff]+ { return yycursor }
	*                     { return -1 }
	*/
}

func lex128HiScalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 0;

	[\x00-\x7f\xc0-\xff]+ { return yycursor }
	*                     { return -1 }
	*/
}

func lex128HiVec16(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 16;

	[\x00-\x7f\xc0-\xff]+ { return yycursor }
	*                     { return -1 }
	*/
}

func lex128HiVec32(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)
	/*!re2c
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;
	re2c:vectorize:loops = 1;
	re2c:vectorize:size = 32;

	[\x00-\x7f\xc0-\xff]+ { return yycursor }
	*                     { return -1 }
	*/
}

func main() {
	buf := make([]byte, 256)
	for n := 0; n <= 128; n++ {
		for i := 0; i < n; i++ {
			buf[i] = 'a'
		}
		buf[n] = '!'
		for i := n + 1; i < len(buf); i++ {
			buf[i] = 0
		}
		want := n
		if n == 0 {
			want = -1
		}
		s16 := &OpaqueGo{raw: buf, pos: 0, end: len(buf)}
		s32 := &OpaqueGo{raw: buf, pos: 0, end: len(buf)}
		if g16 := lexGeneric16(s16); g16 != want {
			panic(fmt.Sprintf("generic16 n=%d: got %d want %d", n, g16, want))
		}
		if g32 := lexGeneric32(s32); g32 != want {
			panic(fmt.Sprintf("generic32 n=%d: got %d want %d", n, g32, want))
		}
	}

	type suite struct {
		name    string
		fillIn  byte
		padExit byte
		sc      func([]byte) int
		v16     func([]byte) int
		v32     func([]byte) int
	}
	suites := []suite{
		{"singleton", 'a', 'x', lexSingletonScalar, lexSingletonVec16, lexSingletonVec32},
		{"0_127", 0x80, 'A', lex0To127Scalar, lex0To127Vec16, lex0To127Vec32},
		{"lo127", 0x10, 'A', lexLo127Scalar, lexLo127Vec16, lexLo127Vec32},
		{"128_255", 'A', 0x80, lex128To255Scalar, lex128To255Vec16, lex128To255Vec32},
		{"128hi", 'A', 0x90, lex128HiScalar, lex128HiVec16, lex128HiVec32},
		{"interior", 'A', 'm', lexInteriorScalar, lexInteriorVec16, lexInteriorVec32},
		{"cross80", 'A', 0x80, lexCross80Scalar, lexCross80Vec16, lexCross80Vec32},
	}
	for _, su := range suites {
		for pos := 0; pos <= 70; pos++ {
			for b := 0; b < 256; b++ {
				slice := buf[:pos+1+64]
				for i := 0; i < pos; i++ {
					slice[i] = su.fillIn
				}
				slice[pos] = byte(b)
				for i := pos + 1; i < len(slice); i++ {
					slice[i] = su.padExit
				}
				want := su.sc(slice)
				g16 := su.v16(slice)
				g32 := su.v32(slice)
				if g16 != want || g32 != want {
					panic(fmt.Sprintf("%s pos=%d b=%02x: want=%d g16=%d g32=%d",
						su.name, pos, b, want, g16, g32))
				}
			}
		}
	}
	fmt.Println("OK: Go 16/32 signed-bias ranges & opaque generic API")
}
