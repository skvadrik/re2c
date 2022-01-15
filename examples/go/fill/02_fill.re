//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"os"
	"strings"
)

/*!max:re2c*/
const BUFSIZE int = 4096

type Input struct {
	file *os.File
	buf  []byte
	cur  int
	tok  int
	lim  int
	eof  bool
}

func fill(in *Input, need int) int {
	if in.eof { return -1 } // unexpected EOF

	// Error: lexeme too long. In real life can reallocate a larger buffer.
	if in.tok < need { return -2 }

	// Shift buffer contents (discard everything up to the current token).
	copy(in.buf[0:], in.buf[in.tok:in.lim])
	in.cur -= in.tok
	in.lim -= in.tok
	in.tok = 0

	// Fill free space at the end of buffer with new data from file.
	n, _ := in.file.Read(in.buf[in.lim:BUFSIZE])
	in.lim += n

	// If read less than expected, this is end of input => add zero padding
	// so that the lexer can access characters at the end of buffer.
	if in.lim < BUFSIZE {
		in.eof = true
		for i := 0; i < YYMAXFILL; i += 1 { in.buf[in.lim+i] = 0 }
		in.lim += YYMAXFILL
	}

	return 0
}

func lex(in *Input) int {
	count := 0
	for {
		in.tok = in.cur
	/*!re2c
		re2c:define:YYCTYPE    = byte;
		re2c:define:YYPEEK     = "in.buf[in.cur]";
		re2c:define:YYSKIP     = "in.cur += 1";
		re2c:define:YYLESSTHAN = "in.lim-in.cur < @@";
		re2c:define:YYFILL     = "if r := fill(in, @@); r != 0 { return r }";

		str = ['] ([^'\\] | [\\][^])* ['];

		[\x00] {
			// Check that it is the sentinel, not some unexpected null.
			if in.tok == in.lim - YYMAXFILL { return count } else { return -1 }
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
	f.WriteString(strings.Repeat(content, BUFSIZE))
	f.Seek(0, 0)
	count := 3 * BUFSIZE // number of quoted strings written to file

	// Prepare lexer state: all offsets are at the end of buffer.
	// This immediately triggers YYFILL, as the YYLESSTHAN condition is true.
	in := &Input{
		file: f,
		buf:  make([]byte, BUFSIZE+YYMAXFILL),
		cur:  BUFSIZE,
		tok:  BUFSIZE,
		lim:  BUFSIZE,
		eof:  false,
	}

	// Run the lexer.
	if lex(in) != count { panic("error"); }

	// Cleanup: remove input file.
	f.Close();
	os.Remove(fname);
}
