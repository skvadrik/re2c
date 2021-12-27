//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"os"
	"strings"
)

const BUFSIZE int = 4096

type Input struct {
	file   *os.File
	data   []byte
	cursor int
	marker int
	token  int
	limit  int
	eof    bool
}

func fill(in *Input) int {
	if in.eof { return -1 } // unexpected EOF

	// Error: lexeme too long. In real life can reallocate a larger buffer.
	if in.token < 1 { return -2 }

	// Shift buffer contents (discard everything up to the current token).
	copy(in.data[0:], in.data[in.token:in.limit])
	in.cursor -= in.token
	in.marker -= in.token
	in.limit -= in.token
	in.token = 0

	// Fill free space at the end of buffer with new data from file.
	n, _ := in.file.Read(in.data[in.limit:BUFSIZE])
	in.limit += n
	in.data[in.limit] = 0

	// If read less than expected, this is the end of input.
	in.eof = in.limit < BUFSIZE

	return 0
}

func lex(in *Input) int {
	count := 0
	for {
		in.token = in.cursor
	/*!re2c
		re2c:eof = 0;
		re2c:define:YYCTYPE    = byte;
		re2c:define:YYPEEK     = "in.data[in.cursor]";
		re2c:define:YYSKIP     = "in.cursor += 1";
		re2c:define:YYBACKUP   = "in.marker = in.cursor";
		re2c:define:YYRESTORE  = "in.cursor = in.marker";
		re2c:define:YYLESSTHAN = "in.limit <= in.cursor";
		re2c:define:YYFILL     = "fill(in) == 0";

		*                           { return -1 }
		$                           { return count }
		['] ([^'\\] | [\\][^])* ['] { count += 1; continue }
		[ ]+                        { continue }
	*/}
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

	// Prepare lexer state (sentinel is set to zero by `make`).
	in := &Input{
		file:   f,
		data:   make([]byte, BUFSIZE+1),
		cursor: BUFSIZE,
		marker: BUFSIZE,
		token:  BUFSIZE,
		limit:  BUFSIZE,
		eof:    false,
	}

	// Run the lexer.
	if lex(in) != count { panic("error"); }

	// Cleanup: remove input file.
	f.Close();
	os.Remove(fname);
}
