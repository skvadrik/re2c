//go:generate re2go $INPUT -o $OUTPUT -i
// --vectorize-linear with yycursor, yymarker and yylimit of type uint, for the simple API without
// YYFILL and for the record API with real refills. Packed 2, 4 and 8 byte reads, their
// code:yylessthan guards and the cursor shifts must type-check with an unsigned cursor, and both
// vector lexers must agree with their scalar twin and with an independent longest-literal oracle
// on every prefix and near miss of the literals. An out-of-range read panics.
package main

import (
	"fmt"
	"strings"
)

/*!max:re2c*/

var words = []string{
	"ab", "abcd", "abcdefgh", "abcdefghijk", "xyzzyxyzzy",
}

type token struct{ rule, length int }

// The longest literal that is a prefix of s, or the default rule with one unit.
func oracle(s string) token {
	want := token{0, 1}
	for i, word := range words {
		if len(word) > want.length || want.rule == 0 {
			if strings.HasPrefix(s, word) {
				want = token{i + 1, len(word)}
			}
		}
	}
	return want
}

/*!rules:re2c:simple
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:yyfill:enable = 0;
	re2c:YYLIMIT = "yylimit";
	"ab"          { return token{1, int(yycursor)} }
	"abcd"        { return token{2, int(yycursor)} }
	"abcdefgh"    { return token{3, int(yycursor)} }
	"abcdefghijk" { return token{4, int(yycursor)} }
	"xyzzyxyzzy"  { return token{5, int(yycursor)} }
	*             { return token{0, int(yycursor)} }
*/

func simple0(yyinput string) token {
	var yycursor, yymarker, yylimit uint = 0, 0, uint(len(yyinput))
	_, _ = yymarker, yylimit
	/*!use:re2c:simple re2c:vectorize:linear = 0; */
}

func simple1(yyinput string) token {
	var yycursor, yymarker, yylimit uint = 0, 0, uint(len(yyinput))
	_, _ = yymarker, yylimit
	/*!use:re2c:simple re2c:vectorize:linear = 1; */
}

type Input struct {
	src                         string
	pos, size, token            uint
	fills                       int
	yyinput                     []byte
	yycursor, yymarker, yylimit uint
	eof                         bool
}

func fill(in *Input, need uint) bool {
	if in.eof {
		return false
	}
	shift := in.token
	if shift < need {
		panic("token does not fit in buffer")
	}
	copy(in.yyinput, in.yyinput[shift:in.yylimit])
	in.yycursor -= shift
	in.yymarker -= shift
	in.yylimit -= shift
	in.token = 0
	in.yyinput = in.yyinput[:cap(in.yyinput)]
	n := uint(copy(in.yyinput[in.yylimit:in.size], in.src[in.pos:]))
	in.pos += n
	in.yylimit += n
	in.fills++
	if in.pos == uint(len(in.src)) {
		in.eof = true
		for i := uint(0); i < YYMAXFILL; i++ {
			in.yyinput[in.yylimit+i] = 0
		}
		in.yylimit += YYMAXFILL
	}
	// Limit reads to initialized input and the required padding.
	in.yyinput = in.yyinput[:in.yylimit]
	return true
}

/*!rules:re2c:filled
	re2c:api = record;
	re2c:YYCTYPE = byte;
	re2c:YYLIMIT = "yyrecord.yylimit";
	re2c:YYFILL = "if !fill(yyrecord, @@) { return -1 }";
	"ab"          { return 1 }
	"abcd"        { return 2 }
	"abcdefgh"    { return 3 }
	"abcdefghijk" { return 4 }
	"xyzzyxyzzy"  { return 5 }
	*             { return 0 }
	"\x00" {
		if yyrecord.eof && yyrecord.token == yyrecord.yylimit-YYMAXFILL { return 100 }
		return 0
	}
*/

func filled0(yyrecord *Input) int {
	/*!use:re2c:filled re2c:vectorize:linear = 0; */
}

func filled1(yyrecord *Input) int {
	/*!use:re2c:filled re2c:vectorize:linear = 1; */
}

var failures, checks int

func checkSimple(s string) {
	in := s + "\x00"
	want := oracle(in)
	got0, got1 := simple0(in), simple1(in)
	checks++
	if got0 != want || got1 != want {
		fmt.Printf("simple %q: scalar %+v, vector %+v, want %+v\n", s, got0, got1, want)
		failures++
	}
}

func checkFilled(src string, size uint, f func(*Input) int, name string) {
	in := &Input{src: src, size: size, yyinput: make([]byte, size+YYMAXFILL),
		yycursor: size, yymarker: size, yylimit: size}
	offset := 0
	for {
		in.token = in.yycursor
		in.yymarker = in.yycursor
		rule := f(in)
		checks++
		if offset == len(src) {
			if rule != 100 || in.yycursor-in.token != 1 {
				fmt.Printf("%s size %d: missing EOF, rule %d\n", name, size, rule)
				failures++
			}
			break
		}
		want := oracle(src[offset:])
		got := token{rule, int(in.yycursor - in.token)}
		if got != want {
			fmt.Printf("%s size %d offset %d: got %+v, want %+v\n", name, size, offset, got, want)
			failures++
			return
		}
		offset += got.length
	}
	if in.pos != uint(len(src)) || (uint(len(src)) > size && in.fills < 2) {
		fmt.Printf("%s: incomplete input or missing refills\n", name)
		failures++
	}
}

func main() {
	alts := []byte{0, 1, 'a', 'z', ':', 0x80, 0xff}
	var corpus strings.Builder
	for _, word := range words {
		for i := 0; i <= len(word); i++ {
			checkSimple(word[:i])
			corpus.WriteString(word[:i] + " ")
			for _, alt := range alts {
				// A prefix followed by a foreign unit, and a near miss with one unit replaced.
				checkSimple(word[:i] + string([]byte{alt}))
				corpus.WriteString(word[:i] + string([]byte{alt}) + " ")
				if i < len(word) {
					near := word[:i] + string([]byte{alt}) + word[i+1:]
					checkSimple(near)
					corpus.WriteString(near + " ")
				}
			}
		}
		for _, other := range words {
			checkSimple(word + other)
			corpus.WriteString(word + other + " ")
		}
	}
	// Retain a partial token as well as YYMAXFILL units of lookahead.
	for size := uint(2 * YYMAXFILL); size <= 3*YYMAXFILL+3; size++ {
		inputs := []string{"", corpus.String(), strings.Repeat(" ", int(size))}
		for _, word := range words {
			for i := 0; i <= len(word); i++ {
				inputs = append(inputs, word[:i])
				// Place each literal across a buffer boundary at every offset.
				inputs = append(inputs, strings.Repeat(" ", int(size)-i)+word)
			}
		}
		for _, src := range inputs {
			checkFilled(src, size, filled0, "fill scalar")
			checkFilled(src, size, filled1, "fill vector")
		}
	}
	if failures > 0 {
		panic(fmt.Sprintf("%d of %d checks failed", failures, checks))
	}
}
