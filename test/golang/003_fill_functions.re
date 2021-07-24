//go:generate re2go $INPUT -o $OUTPUT 
package main

import "fmt"
import "os"

/*!max:re2c*/
var SIZE int = 11

type YYCTYPE = byte
type Input struct {
	file   *os.File
	data   []YYCTYPE
	cursor int
	marker int
	token  int
	limit  int
	eof    bool
}

func fill(in *Input, need int) int {
	// End of input has already been reached, nothing to do.
	if in.eof {
		fmt.Println("fill error: unexpected EOF")
		return 1
	}

	// Check if after moving the current lexeme to the beginning
	// of buffer there will be enough free space.
	if SIZE-(in.cursor-in.token) < need {
		fmt.Println("fill error: lexeme too long")
		return 2
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
	fmt.Printf("fill(%d): %v '%s'\n", need, in.data[:in.limit+1],
		string(in.data[:in.limit]))

	// If read less than expected, this is the end of input.
	in.eof = in.limit < SIZE

	// If end of input, add padding so that the lexer can read
	// the remaining characters at the end of buffer.
	if in.eof {
		for i := 0; i < YYMAXFILL; i += 1 {
			in.data[in.limit+i] = 0
		}
		in.limit += YYMAXFILL
	}

	return 0
}

func Lex(in *Input) int {
	YYPEEK := func() YYCTYPE { return in.data[in.cursor] }
	YYSKIP := func() { in.cursor++ }
	YYBACKUP := func() { in.marker = in.cursor }
	YYRESTORE := func() { in.cursor = in.marker }
	YYLESSTHAN := func(n int) bool { return in.limit-in.cursor < n }
	YYFILL := func(n int) int { return fill(in, n) }

	in.token = in.cursor

	/*!re2c
	re2c:define:YYFILL = "if YYFILL(@@) != 0 { return -2 }";
	re2c:define:YYFILL:naked = 1;
	re2c:api:style = functions;

	* {
		fmt.Println("error")
		return -1
	}

	"\x00" {
		fmt.Println("end")
		return 0
	}

	[0-9]+ {
		fmt.Printf("number-1: %v\n", string(in.data[in.token:in.cursor]))
		return 1
	}

	[0-9]+ [-] [0-9]+ {
		fmt.Printf("number-2: %v\n", string(in.data[in.token:in.cursor]))
		return 2
	}

	[ ] {
		return 3
	}
	*/
}

func test(data string) (result int) {
	tmpfile := "input.txt"

	f, _ := os.Create(tmpfile)
	f.WriteString(data)
	f.WriteString("\000") // lexer expects NULL-terminator
	f.Seek(0, 0)

	defer func() {
		f.Close()
		os.Remove(tmpfile)
	}()

	in := &Input{
		file:   f,
		data:   make([]byte, SIZE+YYMAXFILL),
		cursor: SIZE,
		marker: SIZE,
		token:  SIZE,
		limit:  SIZE,
		eof:    false,
	}

	result = 9999
	for result > 0 {
		result = Lex(in)
	}

	return
}

func main() {
	var s string

	// Succeeds, the lexer has enough characters ahead.
	s = "     123456789      "
	if test(s) != 0 {
		panic("expected 'number: 123456789'")
	}

	// Fails, there is no space for the needed characters.
	s = "     1234567890     "
	if test(s) != -2 {
		panic("expected 'fill error: lexeme too long'")
	}

	// Succeeds, the lexer has enough characters ahead
	// (although the same lexeme length as the previous case,
	// YYFILL argument is smaller in this state).
	s = "     12345-6789     "
	if test(s) != 0 {
		panic("expected 'number: 12345-6789'")
	}

	// Fails, there is no space for any characters.
	s = "     12345-67890     "
	if test(s) != -2 {
		panic("expected 'fill error: lexeme too long'")
	}

	// Fails, invalid input.
	s = "?#!*"
	if test(s) != -1 {
		panic("expected 'error'")
	}

	fmt.Println("OK")
}
