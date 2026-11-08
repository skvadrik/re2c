//go:generate re2go $INPUT -o $OUTPUT -i

// Parity of --vectorize-linear with the ordinary DFA with a YYFILL that does not refill: the input
// is terminated by a zero sentinel and is not padded with YYMAXFILL units, so the YYFILL check does
// not reserve input for the chain. The multi-character reads must stay within the slice, otherwise
// they panic with an index out of range.
package main

/*!rules:re2c:noop
	re2c:api = simple;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYFILL = "// no refill";

	"ab"          { return 1, yycursor }
	"abcd"        { return 2, yycursor }
	"abcdefgh"    { return 3, yycursor }
	"abcdefghijk" { return 4, yycursor }
	"xyzzyxyzzy"  { return 5, yycursor }
	[\x00]        { return 100, yycursor }
	*             { return 0, yycursor }
*/

func lex0(yyinput []byte, yycursor int) (int, int) {
	yylimit, yymarker := len(yyinput), 0
	_ = yymarker
	/*!use:re2c:noop
	re2c:vectorize:linear = 0;
	*/
}

func lex1(yyinput []byte, yycursor int) (int, int) {
	yylimit, yymarker := len(yyinput), 0
	_ = yymarker
	/*!use:re2c:noop
	re2c:vectorize:linear = 1;
	*/
}

func run(lex func([]byte, int) (int, int), s string) []int {
	// Exact size: the input and the sentinel, without YYMAXFILL padding.
	in := append([]byte(s), 0)
	var out []int
	for cur := 0; ; {
		r, next := lex(in, cur)
		out = append(out, r, next)
		if r == 100 || next >= len(in) {
			return out
		}
		cur = next
	}
}

func main() {
	for _, w := range []string{"abcdefghijk", "xyzzyxyzzy"} {
		for n := 0; n <= len(w); n++ {
			a, b := run(lex0, w[:n]), run(lex1, w[:n])
			if len(a) != len(b) {
				panic("token count")
			}
			for i := range a {
				if a[i] != b[i] {
					panic("token")
				}
			}
		}
	}
}
