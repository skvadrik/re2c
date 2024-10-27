//go:generate re2go $INPUT -o $OUTPUT --tags
package main

import (
	"os"
	"reflect"
	"strings"
)

const BUFSIZE int = 4095

type Input struct {
	file     *os.File
	yyinput  []byte
	yycursor int
	yymarker int
	yylimit  int
	token    int
	// Intermediate tag variables must be part of the lexer state passed to YYFILL.
	// They don't correspond to tags and should be autogenerated by re2c.
	/*!stags:re2c format = "\t@@ int\n"; */
	eof      bool
}

type SemVer struct { major, minor, patch int }

func s2n(s []byte) int { // convert pre-parsed string to a number
	n := 0
	for _, c := range s { n = n*10 + int(c-'0') }
	return n
}

func fill(in *Input) int {
	if in.eof { return -1 } // unexpected EOF

	// Error: lexeme too long. In real life can reallocate a larger buffer.
	if in.token < 1 { return -2 }

	// Shift buffer contents (discard everything up to the current token).
	copy(in.yyinput[0:], in.yyinput[in.token:in.yylimit])
	in.yycursor -= in.token
	in.yymarker -= in.token
	in.yylimit -= in.token
	// Tag variables need to be shifted like other input positions. The check
	// for -1 is only needed if some tags are nested inside of alternative or
	// repetition, so that they can have -1 value.
	/*!stags:re2c format = "\tif in.@@ != -1 { in.@@ -= in.token }\n"; */
	in.token = 0

	// Fill free space at the end of buffer with new data from file.
	n, _ := in.file.Read(in.yyinput[in.yylimit:BUFSIZE])
	in.yylimit += n
	in.yyinput[in.yylimit] = 0

	// If read less than expected, this is the end of input.
	in.eof = in.yylimit < BUFSIZE

	return 0
}

func parse(in *Input) []SemVer {
	// Final tag variables available in semantic action.
	/*!svars:re2c format = "var @@ int;"; */

	vers := make([]SemVer, 0)

	for {
		in.token = in.yycursor
	/*!re2c
		re2c:api = record;
		re2c:eof = 0;
		re2c:yyrecord = in;
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "fill(in) == 0";

		num = [0-9]+;

		num @t1 "." @t2 num @t3 ("." @t4 num)? [\n] {
			major := s2n(in.yyinput[in.token:t1])
			minor := s2n(in.yyinput[t2:t3])
			patch := 0
			if t4 != -1 { patch = s2n(in.yyinput[t4:in.yycursor-1]) }
			vers = append(vers, SemVer{major, minor, patch})
			continue
		}
		$ { return vers }
		* { return nil }
	*/
	}
}


func main() () {
	fname := "input"
	content := "1.22.333\n";

	expect := make([]SemVer, 0, BUFSIZE)
	for i := 0; i < BUFSIZE; i += 1 { expect = append(expect, SemVer{1, 22, 333}) }

	// Prepare input file (make sure it exceeds buffer size).
	f, _ := os.Create(fname)
	f.WriteString(strings.Repeat(content, BUFSIZE))
	f.Seek(0, 0)

	// Initialize lexer state: all offsets are at the end of buffer.
	in := &Input{
		file:     f,
		// Sentinel at `yylimit` offset is set to zero, which triggers YYFILL.
		yyinput:  make([]byte, BUFSIZE+1),
		yycursor: BUFSIZE,
		yymarker: BUFSIZE,
		yylimit:  BUFSIZE,
		token:    BUFSIZE,
		eof:      false,
	}

	// Run the lexer and check results.
	if !reflect.DeepEqual(parse(in), expect) { panic("error"); }

	// Cleanup: remove input file.
	f.Close();
	os.Remove(fname);
}
