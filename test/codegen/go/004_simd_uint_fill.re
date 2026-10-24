//go:generate re2go --vectorize-loops $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/bits"
	"simd/archsimd"
	"strings"
)

/*!max:re2c*/

type Input struct {
	yyinput []byte
	yycursor, yylimit, token, base uint
	source *strings.Reader
	chunk int
	eof bool
	fills, shifts, partial int
}

func fill(in *Input, need uint) int {
	if in.eof { return -2 }
	in.fills++
	if in.token != 0 { in.shifts++ }
	if in.yycursor > in.token { in.partial++ }
	copy(in.yyinput, in.yyinput[in.token:in.yylimit])
	in.base += in.token
	in.yycursor -= in.token
	in.yylimit -= in.token
	in.token = 0
	room := len(in.yyinput)-YYMAXFILL-int(in.yylimit)
	nread := min(room, in.chunk)
	if uint(nread)+in.yylimit-in.yycursor < need { return -3 }
	n, _ := in.source.Read(in.yyinput[in.yylimit:int(in.yylimit)+nread])
	in.yylimit += uint(n)
	if in.source.Len() == 0 {
		in.eof = true
		for i := uint(0); i < YYMAXFILL; i++ { in.yyinput[in.yylimit+i] = 0 }
		in.yylimit += YYMAXFILL
	}
	// Poison unused space: vector loads must respect the logical limit.
	for i := int(in.yylimit); i < len(in.yyinput); i++ { in.yyinput[i] = '!' }
	return 0
}

func lexSimd(yyrecord *Input) int {
	/*!re2c
	re2c:api = record;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "if r := fill(yyrecord, @@); r != 0 { return r }";
	re2c:vectorize:loops = 1;
	[a-z]+ { return 1 }
	[ ]+   { return 2 }
	[\x00] { return 0 }
	*      { return -1 }
	*/
}

func lexScalar(yyrecord *Input) int {
	/*!re2c
	re2c:api = record;
	re2c:YYCTYPE = byte;
	re2c:YYFILL = "if r := fill(yyrecord, @@); r != 0 { return r }";
	re2c:vectorize:loops = 0;
	[a-z]+ { return 1 }
	[ ]+   { return 2 }
	[\x00] { return 0 }
	*      { return -1 }
	*/
}

func main() {
	checked := 0
	for _, chunk := range []int{1, 2, 31, 32, 33, 63, 64, 65, 127, 256} {
		for n := 1; n <= 160; n++ {
			data := strings.Repeat(strings.Repeat("a", n)+" ", 5)
			for _, lex := range []func(*Input) int{lexSimd, lexScalar} {
				in := &Input{yyinput: make([]byte, 256+YYMAXFILL), source: strings.NewReader(data), chunk: chunk}
				for k := 0; k <= 10; k++ {
					in.token = in.yycursor
					start := in.base+in.yycursor
					kind, length := 1, uint(n)
					if k%2 == 1 { kind, length = 2, 1 }
					if k == 10 { kind, length = 0, 1 }
					got := lex(in)
					end := in.base+in.yycursor
					wantStart := uint((k/2)*(n+1))
					if k%2 == 1 { wantStart += uint(n) }
					if got != kind || start != wantStart || end != start+length {
						panic(fmt.Sprintf("chunk=%d n=%d token=%d: got=(%d,%d,%d) want=(%d,%d,%d)", chunk, n, k, got, start, end, kind, wantStart, wantStart+length))
					}
				}
				if !in.eof || in.source.Len() != 0 { panic("input not exhausted") }
				if n == 160 && (in.fills < 2 || in.shifts == 0 || in.partial == 0) { panic("refill did not shift a partial token") }
			}
			checked++
		}
	}
	fmt.Printf("OK: %d uint refill inputs bit-exact\n", checked)
}
