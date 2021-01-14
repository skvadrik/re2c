//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"errors"
	"testing"
)

var eBadIP error = errors.New("bad IP")

func lex(str string) (int, error) {
	var cursor, marker, o1, o2, o3, o4 int
	/*!stags:re2c format = 'var @@ int'; separator = "\n\t"; */

	num := func(pos int, end int) int {
		n := 0
		for ; pos < end; pos++ {
			n = n*10 + int(str[pos]-'0')
		}
		return n
	}

	/*!re2c
	re2c:flags:tags = 1;
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";
	re2c:define:YYSTAGP   = "@@{tag} = cursor";
	re2c:define:YYSTAGN   = "@@{tag} = -1";

	octet = [0-9] | [1-9][0-9] | [1][0-9][0-9] | [2][0-4][0-9] | [2][5][0-5];
	dot = [.];
	end = [\x00];

	@o1 octet dot @o2 octet dot @o3 octet dot @o4 octet end {
		return num(o4, cursor-1)+
			(num(o3, o4-1) << 8)+
			(num(o2, o3-1) << 16)+
			(num(o1, o2-1) << 24), nil
	}
	* { return 0, eBadIP }
	*/
}

func TestLex(t *testing.T) {
	var tests = []struct {
		str string
		res int
		err error
	}{
		{"1.2.3.4\000", 0x01020304, nil},
		{"127.0.0.1\000", 0x7f000001, nil},
		{"255.255.255.255\000", 0xffffffff, nil},
		{"1.2.3.\000", 0, eBadIP},
		{"1.2.3.256\000", 0, eBadIP},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			res, err := lex(x.str)
			if !(res == x.res && err == x.err) {
				t.Errorf("got %d, want %d", res, x.res)
			}
		})
	}
}
