//go:generate re2go $INPUT -o $OUTPUT -i
// Parity of --vectorize-linear with the ordinary DFA for the simple API without YYFILL.
// Each rule set is compiled twice, with and without the option; both lexers must return the same
// rule and the same cursor for every prefix and near miss of the literals, with and without
// trailing padding after the sentinel. An out-of-range read panics.
package main

import (
	"fmt"
	"os"
)

/*!rules:re2c:backtrack
	"ab"                         { return 1, yycursor }
	"abcd"                       { return 2, yycursor }
	"abcdefgh"                   { return 3, yycursor }
	"abcdefghijk"                { return 4, yycursor }
	"abcx"                       { return 5, yycursor }
	"bcdefghi"                   { return 6, yycursor }
	"xyzzyxyzzy"                 { return 7, yycursor }
	"q" [0-9]+ "end"             { return 8, yycursor }
	*                            { return 0, yycursor }
*/

func backtrack_0(yyinput string) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!use:re2c:backtrack
		re2c:api = simple;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 0;
		re2c:YYCTYPE = byte;
	*/
}

func backtrack_1(yyinput string) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
/*!use:re2c:backtrack
		re2c:api = simple;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 1;
		re2c:YYCTYPE = byte;
	*/
}

var backtrack_words = []string{
	"\x61\x62",
	"\x61\x62\x63\x64",
	"\x61\x62\x63\x64\x65\x66\x67\x68",
	"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b",
	"\x61\x62\x63\x78",
	"\x62\x63\x64\x65\x66\x67\x68\x69",
	"\x78\x79\x7a\x7a\x79\x78\x79\x7a\x7a\x79",
	"\x71\x31\x32\x33\x65\x6e\x64",
	"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a",
	"\x78\x79\x7a\x7a\x79\x78\x79\x7a\x7a",
}

/*!rules:re2c:anchored
	"GIF89a"                     { return 1, yycursor }
	"GIF87a"                     { return 2, yycursor }
	[\x00\x01]                   { return 3, yycursor }
	[^\x00\x01] [\x00\x01]       { return 3, yycursor }
	[^\x00\x01] [^\x00\x01]      { return 0, yycursor }
*/

func anchored_0(yyinput string) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!use:re2c:anchored
		re2c:api = simple;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 0;
		re2c:YYCTYPE = byte;
	*/
}

func anchored_1(yyinput string) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!use:re2c:anchored
		re2c:api = simple;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 1;
		re2c:YYCTYPE = byte;
	*/
}

var anchored_words = []string{
	"\x47\x49\x46\x38\x39\x61",
	"\x47\x49\x46\x38\x37\x61",
	"\x47\x49\x46\x38",
	"\x47\x49",
	"\x47",
	"\x47\x4a",
}

var failures, checks int

func check1(f, g func(string) (int, int), in string) {
	r1, c1 := f(in)
	r2, c2 := g(in)
	checks++
	if r1 != r2 || c1 != c2 {
		fmt.Fprintf(os.Stderr, "mismatch on %q: rule %d/%d, cursor %d/%d\n", in, r1, r2, c1, c2)
		failures++
	}
}

func check(f, g func(string) (int, int), in string) {
	check1(f, g, in+"\x00")
	pad := in
	for len(pad) < 16 {
		pad += "a"
	}
	check1(f, g, in+"\x00"+pad[:16])
}

func checkSet(f, g func(string) (int, int), ws []string) {
	alt := []byte{0x00, 0x01, 'a', 'z', 'A', 'Z', ':', '-', ' ', '_', '0', 0x7f, 0x80, 0xfe, 0xff}
	for _, w := range ws {
		for i := 0; i <= len(w); i++ {
			check(f, g, w[:i])
			for _, a := range alt {
				check(f, g, w[:i]+string([]byte{a}))
			}
			if i < len(w) {
				check(f, g, w[:i]+string([]byte{w[i] + 1}))
				check(f, g, w[:i]+string([]byte{w[i] - 1}))
			}
		}
		for _, v := range ws {
			check(f, g, w+v)
		}
	}
}

func main() {
	checkSet(backtrack_0, backtrack_1, backtrack_words)
	checkSet(anchored_0, anchored_1, anchored_words)
	if failures > 0 {
		panic(fmt.Sprintf("%d of %d checks failed", failures, checks))
	}
}
