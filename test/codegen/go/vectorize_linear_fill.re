//go:generate re2go $INPUT -o $OUTPUT -i -Wno-vectorize-linear-disabled

// Compare the record API with real refills, with and without the EOF rule.
// The independent longest-literal oracle checks every rule and token length.
package main

import (
	"fmt"
	"strings"
)

/*!max:re2c*/

type Input struct {
	src                         string
	pos, size, token, fills     int
	yyinput                     []byte
	yycursor, yymarker, yylimit int
	eof, eofRule                bool
}

func fill(in *Input, need int) bool {
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
	n := copy(in.yyinput[in.yylimit:in.size], in.src[in.pos:])
	in.pos += n
	in.yylimit += n
	in.fills++
	if in.eofRule {
		in.yyinput[in.yylimit] = 0
		in.eof = in.pos == len(in.src)
		in.yyinput = in.yyinput[:in.yylimit+1]
	} else {
		if in.yylimit < in.size {
			in.eof = true
			for i := 0; i < YYMAXFILL; i++ {
				in.yyinput[in.yylimit+i] = 0
			}
			in.yylimit += YYMAXFILL
		}
		// Limit reads to initialized input and the required padding.
		in.yyinput = in.yyinput[:in.yylimit]
	}
	return true
}

/*!rules:re2c:words
re2c:api = record;
re2c:YYCTYPE = byte;
"ab"                 { return 1 }
"abcdefghijk"        { return 2 }
"xyzzyxyzzy"         { return 3 }
"\x89PNG\r\n\x1a\n" { return 4 }
*                    { return 0 }
*/

/*!rules:re2c:padded
!use:words;
re2c:YYFILL = "if !fill(yyrecord, @@) { return -1 }";
"\x00" {
	if yyrecord.eof && yyrecord.token == yyrecord.yylimit-YYMAXFILL { return 100 }
	return 0
}
*/

func lexFill0(yyrecord *Input) int {
	/*!use:re2c:padded
	re2c:vectorize:linear = 0;
	*/
}

func lexFill1(yyrecord *Input) int {
	/*!use:re2c:padded
	re2c:vectorize:linear = 1;
	*/
}

// With re2c:eof the option is ineffective (YYFILL does not reserve input for a whole chain): re2c
// clears it with a warning (silenced above), so lexEOF0 and lexEOF1 are the same lexer. The pair
// documents that behaviour and keeps the EOF lexer under the oracle.
/*!rules:re2c:ended
!use:words;
re2c:eof = 0;
re2c:YYFILL = "fill(yyrecord, 1)";
$ { return 100 }
*/

func lexEOF0(yyrecord *Input) int {
	/*!use:re2c:ended
	re2c:vectorize:linear = 0;
	*/
}

func lexEOF1(yyrecord *Input) int {
	/*!use:re2c:ended
	re2c:vectorize:linear = 1;
	*/
}

var words = []string{
	"ab", "abcdefghijk", "xyzzyxyzzy", "\x89PNG\r\n\x1a\n",
}

type token struct{ rule, length int }

func check(src string, size int, f func(*Input) int, eofRule bool, name string) {
	pad := YYMAXFILL
	if eofRule {
		pad = 1
	}
	in := &Input{src: src, size: size, yyinput: make([]byte, size+pad),
		yycursor: size, yymarker: size, yylimit: size, eofRule: eofRule}
	offset := 0
	for {
		in.token = in.yycursor
		in.yymarker = in.yycursor
		rule := f(in)
		if offset == len(src) {
			if rule != 100 {
				panic(fmt.Sprintf("%s size %d: missing EOF, rule %d", name, size, rule))
			}
			consumed := 1
			if eofRule {
				consumed = 0
			}
			if in.yycursor-in.token != consumed {
				panic(name + ": wrong cursor at EOF")
			}
			break
		}
		want := token{0, 1}
		for i, word := range words {
			if len(word) > want.length || want.rule == 0 {
				if strings.HasPrefix(src[offset:], word) {
					want = token{i + 1, len(word)}
				}
			}
		}
		got := token{rule, in.yycursor - in.token}
		if got != want {
			panic(fmt.Sprintf("%s size %d offset %d: got %+v, want %+v", name, size, offset, got, want))
		}
		offset += got.length
	}
	if in.pos != len(src) || (len(src) > size && in.fills < 2) {
		panic(fmt.Sprintf("%s: incomplete input or missing refills", name))
	}
}

func main() {
	var corpus strings.Builder
	for _, word := range words {
		for i := 0; i <= len(word); i++ {
			corpus.WriteString(word[:i])
			corpus.WriteByte(' ')
			for _, alt := range []byte{0, 1, 'a', 'z', ':', 0x80, 0xff} {
				corpus.WriteString(word[:i])
				corpus.WriteByte(alt)
				corpus.WriteByte(' ')
			}
		}
		for _, other := range words {
			corpus.WriteString(word + other + " ")
		}
	}
	cases := []struct {
		name string
		lex  func(*Input) int
		eof  bool
	}{
		{"fill scalar", lexFill0, false}, {"fill vector", lexFill1, false},
		{"EOF scalar", lexEOF0, true}, {"EOF vector", lexEOF1, true},
	}
	// Retain a partial token as well as YYMAXFILL units of lookahead.
	for size := 2*YYMAXFILL; size <= 3*YYMAXFILL+3; size++ {
		inputs := []string{"", corpus.String(), strings.Repeat(" ", size), strings.Repeat(" ", 2*size)}
		// Every prefix also occurs at the physical end, not just before a separator.
		for _, word := range words {
			for i := 0; i <= len(word); i++ {
				inputs = append(inputs, word[:i])
				// Place each literal across a buffer boundary at every offset.
				inputs = append(inputs, strings.Repeat(" ", size-i)+word)
			}
		}
		for _, src := range inputs {
			for _, c := range cases {
				check(src, size, c.lex, c.eof, c.name)
			}
		}
	}
}
