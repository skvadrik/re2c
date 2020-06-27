//go:generate "${RE2C}" --lang go "${GOFILE}" -o example_test.go
package main

import "testing"

const (
	err = iota
	bin
	oct
	dec
	hex
)

func lex(str string) int {
	var cursor, marker int

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	end = "\x00";
	bin = '0b' [01]+;
	oct = "0" [0-7]*;
	dec = [1-9][0-9]*;
	hex = '0x' [0-9a-fA-F]+;

	*       { return err }
	bin end { return bin }
	oct end { return oct }
	dec end { return dec }
	hex end { return hex }
	*/
}

func TestLex(t *testing.T) {
	var tests = []struct {
		res int
		str string
	}{
		{err, "\000"},
		{bin, "0b1101\000"},
		{oct, "0644\000"},
		{dec, "1234567890\000"},
		{hex, "0x7ef\000"},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			res := lex(x.str)
			if res != x.res {
				t.Errorf("got %d, want %d", res, x.res)
			}
		})
	}
}
