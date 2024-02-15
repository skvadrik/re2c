//go:generate re2go $INPUT -o $OUTPUT --recursive-functions -i
package main

import (
	"os"
	"strings"
)

/*!max:re2c*/
const BUFSIZE uint = 4096

type Input struct {
	file  *os.File
	buf   []byte
	cur   uint
	tok   uint
	lim   uint
	eof   bool
	count int
}

func fill(in *Input, need uint) int {
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
	in.lim += uint(n)

	// If read less than expected, this is end of input => add zero padding
	// so that the lexer can access characters at the end of buffer.
	if in.lim < BUFSIZE {
		in.eof = true
		for i := uint(0); i < YYMAXFILL; i += 1 { in.buf[in.lim+i] = 0 }
		in.lim += YYMAXFILL
	}

	return 0
}

/*!re2c
	re2c:define:YYFN       = ["lex;int", "in;*Input"];
	re2c:define:YYCTYPE    = byte;
	re2c:define:YYPEEK     = "in.buf[in.cur]";
	re2c:define:YYSKIP     = "in.cur += 1";
	re2c:define:YYLESSTHAN = "in.lim-in.cur < @@";
	re2c:define:YYFILL     = "if r := fill(in, @@); r != 0 { return r }";

	str = ['] ([^'\\] | [\\][^])* ['];

	[\x00] { return in.count; }
	str    { in.count += 1; return lex_loop(in) }
	[ ]+   { return lex_loop(in) }
	*      { return -1 }
*/

func lex_loop(in *Input) int {
	in.tok = in.cur
	return lex(in)
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
		file:  f,
		buf:   make([]byte, BUFSIZE+YYMAXFILL),
		cur:   BUFSIZE,
		tok:   BUFSIZE,
		lim:   BUFSIZE,
		eof:   false,
		count: 0,
	}

	// Run the lexer.
	if lex_loop(in) != count { panic("error"); }

	// Cleanup: remove input file.
	f.Close();
	os.Remove(fname);
}
