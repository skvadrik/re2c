//go:generate re2go $INPUT -o $OUTPUT -ci
package main

import "fmt"

/*!types:re2c*/

func Lex(str string) int {
	var cursor int
	cond := yycinit
	n := 0

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";
	re2c:define:YYGETCONDITION = "cond";
	re2c:define:YYSETCONDITION = "cond = @@";
	re2c:define:YYSHIFT = "cursor += @@";

	end = [\x00];

	<*> * { return -1 }

	<init> '0b'       :=> bin
	<init> "0"        :=> oct
	<init> "" / [1-9] :=> dec
	<init> '0x'       :=> hex

	<bin, oct, dec, hex> end { return n }

	<bin> [01]  { n = n*2 + int(str[cursor-1] - '0'); goto yyc_bin; }
	<oct> [0-7] { n = n*8 + int(str[cursor-1] - '0'); goto yyc_oct; }
	<dec> [0-9] { n = n*10 + int(str[cursor-1] - '0'); goto yyc_dec; }
	<hex> [0-9] { n = n*16 + int(str[cursor-1] - '0'); goto yyc_hex; }
	<hex> [a-f] { n = n*16 + int(str[cursor-1] - 'a') + 10; goto yyc_hex; }
	<hex> [A-F] { n = n*16 + int(str[cursor-1] - 'A') + 10; goto yyc_hex; }
	*/
}

func test(str string, num int) {
	if res := Lex(str); res != num {
		panic(fmt.Sprintf("failed %s: expected %d, got %d", str, num, res))
	}
}

func main() {
	test("123\000", 123)
	test("0b101\000", 5)
	test("0x10Ff\000", 4096 + 255)
	test("0112\000", 74)
	test("0\000", 0)
	test("\000", -1)
}
