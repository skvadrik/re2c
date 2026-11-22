//go:generate re2go --arch x86 --vectorize-loops --loop-switch -f $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
	"strings"
)

type State struct {
	yyinput  []byte
	yycursor int
	yylimit  int
	yymarker int
	yych     byte
	yystate  int
}

func lexRecord(st *State) int {
	/*!re2c
	re2c:api = record;
	re2c:yyrecord = st;
	re2c:YYCTYPE = byte;
	re2c:yych = "st.yych";
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	[a-zA-Z_][a-zA-Z0-9_]* ";" { return 1 }
	*                          { return -1 }
	*/
}

func lexGeneric(st *State) int {
	/*!re2c
	re2c:api = generic;
	re2c:api:style = free-form;
	re2c:api:sigil = "@@";
	re2c:YYCTYPE = byte;
	re2c:YYPEEK = "st.yyinput[st.yycursor]";
	re2c:YYPEEK32 = "archsimd.LoadUint8x32(st.yyinput[st.yycursor : st.yycursor+32]).AsInt8x32()";
	re2c:YYPEEK16 = "archsimd.LoadUint8x16(st.yyinput[st.yycursor : st.yycursor+16]).AsInt8x16()";
	re2c:YYSKIP = "st.yycursor++";
	re2c:YYBACKUP = "st.yymarker = st.yycursor";
	re2c:YYRESTORE = "st.yycursor = st.yymarker";
	re2c:YYSHIFT = "st.yycursor += @@";
	re2c:YYLESSTHAN = "(st.yylimit - st.yycursor) < @@";
	re2c:YYGETSTATE = "st.yystate";
	re2c:YYSETSTATE = "st.yystate = @@";
	re2c:yych = "st.yych";
	re2c:YYFILL = "return -2";
	re2c:YYFILL:naked = 1;

	[a-zA-Z_][a-zA-Z0-9_]* ";" { return 1 }
	*                          { return -1 }
	*/
}

func main() {
	raw := []byte(strings.Repeat("a", 95) + ";" + strings.Repeat("\x00", 64))
	for _, fn := range []func(*State) int{lexRecord, lexGeneric} {
		st := &State{
			yyinput:  raw,
			yycursor: 0,
			yylimit:  50,
			yystate:  -1,
		}
		if got := fn(st); got != -2 {
			panic(fmt.Sprintf("expected -2 on partial buffer, got %d", got))
		}
		st.yylimit = len(raw)
		if got := fn(st); got != 1 || st.yycursor != 96 {
			panic(fmt.Sprintf("expected (1, 96), got (%d, %d)", got, st.yycursor))
		}
	}
	fmt.Println("OK")
}
