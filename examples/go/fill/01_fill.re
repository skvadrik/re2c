//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"os"
	"strings"
)

const BUFSIZE int = 4096

type Input struct {
	file *os.File
	buf  []byte
	cur  int
	mar  int
	tok  int
	lim  int
	eof  bool
}

func fill(in *Input) int {
	if in.eof { return -1 } // unexpected EOF

	// Error: lexeme too long. In real life can reallocate a larger buffer.
	if in.tok < 1 { return -2 }

	// Shift buffer contents (discard everything up to the current token).
	copy(in.buf[0:], in.buf[in.tok:in.lim])
	in.cur -= in.tok
	in.mar -= in.tok
	in.lim -= in.tok
	in.tok = 0

	// Fill free space at the end of buffer with new data from file.
	n, _ := in.file.Read(in.buf[in.lim:BUFSIZE])
	in.lim += n
	in.buf[in.lim] = 0

	// If read less than expected, this is the end of input.
	in.eof = in.lim < BUFSIZE

	return 0
}

func lex(in *Input) int {
	count := 0
	for {
		in.tok = in.cur
	/*!re2c
		re2c:eof = 0;
		re2c:define:YYCTYPE    = byte;
		re2c:define:YYPEEK     = "in.buf[in.cur]";
		re2c:define:YYSKIP     = "in.cur += 1";
		re2c:define:YYBACKUP   = "in.mar = in.cur";
		re2c:define:YYRESTORE  = "in.cur = in.mar";
		re2c:define:YYLESSTHAN = "in.lim <= in.cur";
		re2c:define:YYFILL     = "fill(in) == 0";

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
	f.WriteString(strings.Repeat(content, BUFSIZE))
	f.Seek(0, 0)
	count := 3 * BUFSIZE // number of quoted strings written to file

	// Prepare lexer state: all offsets are at the end of buffer.
	in := &Input{
		file: f,
		// Sentinel at `lim` offset is set to zero, which triggers YYFILL.
		buf:  make([]byte, BUFSIZE+1),
		cur:  BUFSIZE,
		mar:  BUFSIZE,
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
