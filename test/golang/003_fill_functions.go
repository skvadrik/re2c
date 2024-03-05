// Code generated by re2c, DO NOT EDIT.
//line "golang/003_fill_functions.re":1
//go:generate re2go $INPUT -o $OUTPUT 
package main

import "fmt"
import "os"

//line "golang/003_fill_functions.go":10
const YYMAXFILL = 2
//line "golang/003_fill_functions.re":7

var SIZE uint = 11

type YYCTYPE = byte
type Input struct {
	file   *os.File
	data   []YYCTYPE
	cursor uint
	marker uint
	token  uint
	limit  uint
	eof    bool
}

func fill(in *Input, need uint) int {
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
	in.limit += uint(n)
	fmt.Printf("fill(%d): %v '%s'\n", need, in.data[:in.limit+1],
		string(in.data[:in.limit]))

	// If read less than expected, this is the end of input.
	in.eof = in.limit < SIZE

	// If end of input, add padding so that the lexer can read
	// the remaining characters at the end of buffer.
	if in.eof {
		for i := uint(0); i < YYMAXFILL; i += 1 {
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
	YYLESSTHAN := func(n uint) bool { return in.limit-in.cursor < n }
	YYFILL := func(n uint) int { return fill(in, n) }

	in.token = in.cursor

	
//line "golang/003_fill_functions.go":81
{
	var yych YYCTYPE
	if (YYLESSTHAN(1)) {
		if YYFILL(1) != 0 { return -2 }
	}
	yych = YYPEEK()
	switch (yych) {
	case 0x00:
		goto yy1
	case ' ':
		goto yy3
	case '0','1','2','3','4','5','6','7','8','9':
		goto yy4
	default:
		goto yy2
	}
yy1:
	YYSKIP()
//line "golang/003_fill_functions.re":84
	{
		fmt.Println("end")
		return 0
	}
//line "golang/003_fill_functions.go":105
yy2:
	YYSKIP()
//line "golang/003_fill_functions.re":79
	{
		fmt.Println("error")
		return -1
	}
//line "golang/003_fill_functions.go":113
yy3:
	YYSKIP()
//line "golang/003_fill_functions.re":99
	{
		return 3
	}
//line "golang/003_fill_functions.go":120
yy4:
	YYSKIP()
	YYBACKUP()
	if (YYLESSTHAN(2)) {
		if YYFILL(2) != 0 { return -2 }
	}
	yych = YYPEEK()
	switch (yych) {
	case '-':
		goto yy6
	case '0','1','2','3','4','5','6','7','8','9':
		goto yy4
	default:
		goto yy5
	}
yy5:
//line "golang/003_fill_functions.re":89
	{
		fmt.Printf("number-1: %v\n", string(in.data[in.token:in.cursor]))
		return 1
	}
//line "golang/003_fill_functions.go":142
yy6:
	YYSKIP()
	yych = YYPEEK()
	switch (yych) {
	case '0','1','2','3','4','5','6','7','8','9':
		goto yy8
	default:
		goto yy7
	}
yy7:
	YYRESTORE()
	goto yy5
yy8:
	YYSKIP()
	if (YYLESSTHAN(1)) {
		if YYFILL(1) != 0 { return -2 }
	}
	yych = YYPEEK()
	switch (yych) {
	case '0','1','2','3','4','5','6','7','8','9':
		goto yy8
	default:
		goto yy9
	}
yy9:
//line "golang/003_fill_functions.re":94
	{
		fmt.Printf("number-2: %v\n", string(in.data[in.token:in.cursor]))
		return 2
	}
//line "golang/003_fill_functions.go":173
}
//line "golang/003_fill_functions.re":102

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
