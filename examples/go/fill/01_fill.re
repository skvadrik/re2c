//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"os"
	"strings"
)

const BUFSIZE uint = 4096

type Input struct {
	file     *os.File
	yyinput  []byte
	yycursor uint
	yymarker uint
	yylimit  uint
	token    uint
	eof      bool
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
	in.token = 0

	// Fill free space at the end of buffer with new data from file.
	n, _ := in.file.Read(in.yyinput[in.yylimit:BUFSIZE])
	in.yylimit += uint(n)
	in.yyinput[in.yylimit] = 0

	// If read less than expected, this is the end of input.
	in.eof = in.yylimit < BUFSIZE

	return 0
}

func lex(yyrecord *Input) int {
	count := 0
	for {
		yyrecord.token = yyrecord.yycursor
	/*!re2c
		re2c:api = record;
		re2c:eof = 0;
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "fill(yyrecord) == 0";

		str = ['] ([^'\\] | [\\][^])* ['];

		*    { return -1 }
		$    { return count }
		str  { count += 1; continue }
		[ ]+ { continue }
	*/
	}
}

func main() () {
	fname := "input"
	content := "'qu\000tes' 'are' 'fine: \\'' ";

	// Prepare input file: a few times the size of the buffer, containing
	// strings with zeroes and escaped quotes.
	f, _ := os.Create(fname)
	f.WriteString(strings.Repeat(content, int(BUFSIZE)))
	f.Seek(0, 0)
	count := 3 * int(BUFSIZE) // number of quoted strings written to file

	// Prepare lexer state: all offsets are at the end of buffer.
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

	// Run the lexer.
	if lex(in) != count { panic("error"); }

	// Cleanup: remove input file.
	f.Close();
	os.Remove(fname);
}
