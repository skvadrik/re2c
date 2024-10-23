//go:generate re2go -c $INPUT -o $OUTPUT -i --api simple
package main

import "errors"

var (
	eSyntax   = errors.New("syntax error")
	eOverflow = errors.New("overflow error")
)

/*!conditions:re2c*/

const u32Limit uint64 = 1<<32

func parse_u32(yyinput string) (uint32, error) {
	var yycursor, yymarker int
	result := uint64(0)
	yycond := yycinit

	add := func(base uint64, offset byte) {
		result = result * base + uint64(yyinput[yycursor-1] - offset)
		if result >= u32Limit {
			result = u32Limit
		}
	}

	/*!re2c
		re2c:yyfill:enable = 0;
		re2c:YYCTYPE = byte;
		re2c:YYGETCOND = "cond";
		re2c:YYSETCOND = "cond = @@";

		<*> * { return 0, eSyntax }

		<init> '0b' / [01]        :=> bin
		<init> "0"                :=> oct
		<init> ""   / [1-9]       :=> dec
		<init> '0x' / [0-9a-fA-F] :=> hex

		<bin, oct, dec, hex> "\x00" {
			if result < u32Limit {
				return uint32(result), nil
			} else {
				return 0, eOverflow
			}
		}

		<bin> [01]  { add(2, '0');     goto yyc_bin }
		<oct> [0-7] { add(8, '0');     goto yyc_oct }
		<dec> [0-9] { add(10, '0');    goto yyc_dec }
		<hex> [0-9] { add(16, '0');    goto yyc_hex }
		<hex> [a-f] { add(16, 'a'-10); goto yyc_hex }
		<hex> [A-F] { add(16, 'A'-10); goto yyc_hex }
	*/
}

func main() {
	test := func(num uint32, str string, err error) {
		if n, e := parse_u32(str); !(n == num && e == err) {
			panic("error")
		}
	}
	test(1234567890, "1234567890\000", nil)
	test(13, "0b1101\000", nil)
	test(0x7fe, "0x007Fe\000", nil)
	test(0644, "0644\000", nil)
	test(0, "9999999999\000", eOverflow)
	test(0, "123??\000", eSyntax)
}
