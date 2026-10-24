//go:generate re2go $INPUT -o $OUTPUT -i
// A type parameter named byte must fail in the Go compiler, not at run time.
// go build of this generated file must fail with "array length ... must be constant".
package main

import "fmt"

func lex[byte ~uint8 | ~int8 | ~uint16](yyinput []byte) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!re2c
		re2c:api = simple;
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 1;
		"abcdefgh" { return 1, yycursor }
		*          { return 0, yycursor }
		[\x00]     { return -1, yycursor }
	*/
}

func main() {
	r, c := lex([]int8{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 0})
	fmt.Printf("generic %d,%d\n", r, c)
}
