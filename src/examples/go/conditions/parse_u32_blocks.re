//go:generate re2go -c $INPUT -o $OUTPUT -i
package main

import (
	"errors"
	"testing"
)

var (
	eSyntax   = errors.New("syntax error")
	eOverflow = errors.New("overflow error")
)

const u32Limit uint64 = 1<<32

func parse_u32(str string) (uint32, error) {
	var cursor, marker int
	result := uint64(0)

	add_digit := func(base uint64, offset byte) {
		result = result * base + uint64(str[cursor-1] - offset)
		if result >= u32Limit {
			result = u32Limit
		}
	}

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYSHIFT   = "cursor += @@{shift}";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	end = "\x00";

	'0b' / [01]        { goto bin }
	"0"                { goto oct }
	""   / [1-9]       { goto dec }
	'0x' / [0-9a-fA-F] { goto hex }
	*                  { goto err }
	*/
bin:
	/*!re2c
	end   { goto end }
	[01]  { add_digit(2, '0'); goto bin }
	*     { goto err }
	*/
oct:
	/*!re2c
	end   { goto end }
	[0-7] { add_digit(8, '0'); goto oct }
	*     { goto err }
	*/
dec:
	/*!re2c
	end   { goto end }
	[0-9] { add_digit(10, '0'); goto dec }
	*     { goto err }
	*/
hex:
	/*!re2c
	end   { goto end }
	[0-9] { add_digit(16, '0');    goto hex }
	[a-f] { add_digit(16, 'a'-10); goto hex }
	[A-F] { add_digit(16, 'A'-10); goto hex }
	*     { goto err }
	*/
end:
	if result < u32Limit {
		return uint32(result), nil
	} else {
		return 0, eOverflow
	}
err:
	return 0, eSyntax
}

func TestLex(t *testing.T) {
	var tests = []struct {
		num uint32
		str string
		err error
	}{
		{1234567890, "1234567890\000", nil},
		{13, "0b1101\000", nil},
		{0x7fe, "0x007Fe\000", nil},
		{0644, "0644\000", nil},
		{0, "9999999999\000", eOverflow},
		{0, "123??\000", eSyntax},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			num, err := parse_u32(x.str)
			if !(num == x.num && err == x.err) {
				t.Errorf("got %d, want %d", num, x.num)
			}
		})
	}
}
