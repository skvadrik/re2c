//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"os"
	"strings"
)

/*!max:re2c*/
const BUFSIZE uint = 4096

type Input struct {
	file     *os.File
	yyinput  []byte
	yycursor uint
	yylimit  uint
	token    uint
	eof      bool
}

func fill(in *Input, need uint) int {
	if in.eof { return -1 } // unexpected EOF

	// Error: lexeme too long. In real life can reallocate a larger buffer.
	if in.token < need { return -2 }

	// Shift buffer contents (discard everything up to the current token).
	copy(in.yyinput[0:], in.yyinput[in.token:in.yylimit])
	in.yycursor -= in.token
	in.yylimit -= in.token
	in.token = 0

	// Fill free space at the end of buffer with new data from file.
	n, _ := in.file.Read(in.yyinput[in.yylimit:BUFSIZE])
	in.yylimit += uint(n)

	// If read less than expected, this is end of input => add zero padding
	// so that the lexer can access characters at the end of buffer.
	if in.yylimit < BUFSIZE {
		in.eof = true
		for i := uint(0); i < YYMAXFILL; i += 1 { in.yyinput[in.yylimit+i] = 0 }
		in.yylimit += YYMAXFILL
	}

	return 0
}

func lex(yyrecord *Input) int {
	count := 0
	for {
		yyrecord.token = yyrecord.yycursor
	/*!re2c
		re2c:api = record;
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "if r := fill(yyrecord, @@); r != 0 { return r }";

		str = ['] ([^'\\] | [\\][^])* ['];

		[\x00] {
			// Check that it is the sentinel, not some unexpected null.
			if yyrecord.token == yyrecord.yylimit - YYMAXFILL { return count } else { return -1 }
		}
		str  { count += 1; continue }
		[ ]+ { continue }
		*    { return -1 }
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
	// This immediately triggers YYFILL, as the YYLESSTHAN condition is true.
	in := &Input{
		file:     f,
		yyinput:  make([]byte, BUFSIZE+YYMAXFILL),
		yycursor: BUFSIZE,
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
