//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"errors"
	"testing"
)

/*!maxnmatch:re2c*/

var eBadIP error = errors.New("bad IP")

func lex(str string) (int, error) {
	var cursor, marker, yynmatch int
	yypmatch := make([]int, YYMAXNMATCH*2)
	/*!stags:re2c format = '\tvar @@ int\n'; */

	num := func(pos int, end int) int {
		n := 0
		for ; pos < end; pos++ {
			n = n*10 + int(str[pos]-'0')
		}
		return n
	}

	/*!re2c
	re2c:flags:posix-captures = 1;
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE     = byte;
	re2c:define:YYPEEK      = "str[cursor]";
	re2c:define:YYSKIP      = "cursor += 1";
	re2c:define:YYBACKUP    = "marker = cursor";
	re2c:define:YYRESTORE   = "cursor = marker";
	re2c:define:YYSTAGP     = "@@{tag} = cursor";
	re2c:define:YYSTAGN     = "@@{tag} = -1";
	re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";

	octet = [0-9] | [1-9][0-9] | [1][0-9][0-9] | [2][0-4][0-9] | [2][5][0-5];
	dot = [.];
	end = [\x00];

	(octet) dot (octet) dot (octet) dot (octet) end {
		if yynmatch != 5 {
			panic("expected 5 submatch groups")
		}
		return num(yypmatch[8], yypmatch[9])+
			(num(yypmatch[6], yypmatch[7]) << 8)+
			(num(yypmatch[4], yypmatch[5]) << 16)+
			(num(yypmatch[2], yypmatch[3]) << 24), nil
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
