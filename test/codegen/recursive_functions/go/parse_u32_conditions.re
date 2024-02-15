//go:generate re2go -c $INPUT -o $OUTPUT --recursive-functions -i
package main

import "errors"

var (
	eSyntax   = errors.New("syntax error")
	eOverflow = errors.New("overflow error")
)

/*!conditions:re2c*/

const u32Limit uint64 = 1<<32

type State struct {
	str    string
	cur    int
	mar    int
	cond   uint
	result uint64
}

func add(st *State, base uint64, offset byte) {
	st.result = st.result * base + uint64(st.str[st.cur-1] - offset)
	if st.result >= u32Limit {
		st.result = u32Limit
	}
}

/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYFN           = ["lex;(uint32, error)", "st;*State"];
	re2c:define:YYCTYPE        = byte;
	re2c:define:YYPEEK         = "st.str[st.cur]";
	re2c:define:YYSKIP         = "st.cur += 1";
	re2c:define:YYSHIFT        = "st.cur += @@{shift}";
	re2c:define:YYBACKUP       = "st.mar = st.cur";
	re2c:define:YYRESTORE      = "st.cur = st.mar";
	re2c:define:YYGETCONDITION = "st.cond";
	re2c:define:YYSETCONDITION = "st.cond = @@";

	<*> * { return 0, eSyntax }

	<init> '0b' / [01]        :=> bin
	<init> "0"                :=> oct
	<init> ""   / [1-9]       :=> dec
	<init> '0x' / [0-9a-fA-F] :=> hex

	<bin, oct, dec, hex> "\x00" {
		if st.result < u32Limit {
			return uint32(st.result), nil
		} else {
			return 0, eOverflow
		}
	}

	<bin> [01]  { add(st, 2, '0');     return yyfnbin(st) }
	<oct> [0-7] { add(st, 8, '0');     return yyfnoct(st) }
	<dec> [0-9] { add(st, 10, '0');    return yyfndec(st) }
	<hex> [0-9] { add(st, 16, '0');    return yyfnhex(st) }
	<hex> [a-f] { add(st, 16, 'a'-10); return yyfnhex(st) }
	<hex> [A-F] { add(st, 16, 'A'-10); return yyfnhex(st) }
*/

func parse_u32(str string) (uint32, error) {
	st := &State{
		str:    str,
		cur:    0,
		mar:    0,
		cond:   yycinit,
		result: uint64(0),
	}
	return lex(st)
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
