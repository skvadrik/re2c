//go:generate re2go $INPUT -o $OUTPUT -i
// Shadowing the predeclared byte must fail in the Go compiler, not in re2c.
// go build of this generated file must fail with "index out of bounds".
package main

import "fmt"

type byte = uint16

func shadowConv(yyinput []byte) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!re2c
		re2c:api = simple;
		re2c:YYCTYPE = byte;
		re2c:yych:conversion = 1;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 1;
		"abcdefgh" { return 1, yycursor }
		*          { return 0, yycursor }
		[\x00]     { return -1, yycursor }
	*/
}

func shadowPlain(yyinput []byte) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!re2c
		re2c:api = simple;
		re2c:YYCTYPE = byte;
		re2c:yych:conversion = 0;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 1;
		"abcdefgh" { return 1, yycursor }
		*          { return 0, yycursor }
		[\x00]     { return -1, yycursor }
	*/
}

func main() {
	in := []byte{'a', 'b', 'c', 'd', 0x165, 'f', 'g', 'h', 0}
	r0, c0 := shadowConv(in)
	r1, c1 := shadowPlain(in)
	fmt.Printf("width scalar=%d,%d plain=%d,%d\n", r0, c0, r1, c1)
}
