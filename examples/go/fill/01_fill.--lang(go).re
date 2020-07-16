//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"os"
	"testing"
)

// Intentionally small to trigger buffer refill.
const SIZE int = 16

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
	// If nothing can be read, fail.
	if in.eof {
		return 1
	}

	// Check if at least some space can be freed.
	if in.token == 0 {
		// In real life can reallocate a larger buffer.
		panic("fill error: lexeme too long")
	}

	// Discard everything up to the start of the current lexeme,
	// shift buffer contents and adjust offsets.
	copy(in.data[0:], in.data[in.token:in.limit])
	in.cursor -= in.token
	in.marker -= in.token
	in.limit -= in.token
	in.token = 0

	// Read new data (as much as possible to fill the buffer).
	n, _ := in.file.Read(in.data[in.limit:SIZE])
	in.limit += n
	in.data[in.limit] = 0

	// If read less than expected, this is the end of input.
	in.eof = in.limit < SIZE

	// If nothing has been read, fail.
	if n == 0 {
		return 1
	}

	return 0
}

func lex(in *Input) int {
	count := 0
loop:
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
	['] ([^'\\] | [\\][^])* ['] { count += 1; goto loop }
	[ ]+                        { goto loop }
	*/
}

// Prepare a file with the input text and run the lexer.
func test(data string) (result int) {
	tmpfile := "input.txt"

	f, _ := os.Create(tmpfile)
	f.WriteString(data)
	f.Seek(0, 0)

	defer func() {
		if r := recover(); r != nil {
			result = -2
		}
		f.Close()
		os.Remove(tmpfile)
	}()

	in := &Input{
		file:   f,
		data:   make([]byte, SIZE+1),
		cursor: SIZE,
		marker: SIZE,
		token:  SIZE,
		limit:  SIZE,
		eof:    false,
	}

	return lex(in)
}

func TestLex(t *testing.T) {
	var tests = []struct {
		res int
		str string
	}{
		{0, ""},
		{2, "'one' 'two'"},
		{3, "'qu\000tes' 'are' 'fine: \\'' "},
		{-1, "'unterminated\\'"},
		{-2, "'loooooooooooong'"},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			res := test(x.str)
			if res != x.res {
				t.Errorf("got %d, want %d", res, x.res)
			}
		})
	}
}
