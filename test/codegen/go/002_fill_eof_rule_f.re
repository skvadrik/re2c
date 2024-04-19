//go:generate re2go $INPUT -o $OUTPUT -f
package main

import "fmt"
import "os"

var SIZE int = 11

type YYCTYPE byte
type Input struct {
	file   *os.File
	data   []byte
	cursor int
	marker int
	token  int
	limit  int
	eof    bool
	state  int
}

const (
	lexError = iota
	lexNeedMoreSpace
	lexNeedMoreInput
	lexResume
	lexEnd
	lexNumber1
	lexNumber2
	lexSpace
)

func fill(in *Input) int {
	// Nothing can be read, resume lexing to match EOF rule or fail.
	if in.eof {
		return lexResume
	}

	// Check if at least some space can be freed.
	if in.token == 0 {
		// In real life can reallocate a larger buffer.
		fmt.Println("fill error: lexeme too long")
		return lexNeedMoreSpace
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
	fmt.Printf("fill: %v '%s'\n", in.data[:in.limit+1],
		string(in.data[:in.limit]))

	// If read less than expected, this is the end of input.
	in.eof = in.limit < SIZE

	return lexResume
}

func Lex(in *Input) int {
	var yych YYCTYPE

	/*!re2c
	re2c:eof = 0;
	re2c:define:YYPEEK = "YYCTYPE(in.data[in.cursor])";
	re2c:define:YYSKIP = "in.cursor += 1";
	re2c:define:YYBACKUP  = "in.marker = in.cursor";
	re2c:define:YYRESTORE = "in.cursor = in.marker";
	re2c:define:YYLESSTHAN = "in.limit-in.cursor < @@";
	re2c:define:YYFILL = "return lexNeedMoreInput";
	re2c:define:YYGETSTATE = "in.state";
	re2c:define:YYSETSTATE = "in.state = @@";

	* {
		fmt.Println("error")
		return lexError
	}

	$ {
		fmt.Println("end")
		return lexEnd
	}

	[0-9]+ {
		fmt.Printf("number-1: %v\n", string(in.data[in.token:in.cursor]))
		return lexNumber1
	}

	[0-9]+ [-] [0-9]+ {
		fmt.Printf("number-2: %v\n", string(in.data[in.token:in.cursor]))
		return lexNumber2
	}

	[ ]+ {
		return lexSpace
	}
	*/
}

func test(data string) int {
	tmpfile := "input.txt"

	f, _ := os.Create(tmpfile)
	f.WriteString(data)
	f.Seek(0, 0)

	defer func() {
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

	result := lexNeedMoreInput
loop:
	for {
		switch result {
		case lexError:
			break loop
		case lexEnd:
			break loop
		case lexNeedMoreInput:
			result = fill(in)
			if result != lexResume {
				break loop
			}
		default:
			in.token = in.cursor
			in.state = 0
		}
		result = Lex(in)
	}

	return result
}

func main() {
	var s string

	// Succeeds, the lexer needs 1 character ahead.
	s = "     1234567890     "
	if test(s) != lexEnd {
		panic("expected 'number: 1234567890'")
	}

	// Fails, the lexer needs 1 character ahead, but there is no space.
	s = "     12345678901    "
	if test(s) != lexNeedMoreSpace {
		panic("expected 'fill error: lexeme too long'")
	}

	// Succeeds, the lexer needs 1 character ahead.
	s = "     12345-6789     "
	if test(s) != lexEnd {
		panic("expected 'number: 12345-6789'")
	}

	// Fails, the lexer needs 1 character ahead, but there is no space.
	s = "     12345-67890     "
	if test(s) != lexNeedMoreSpace {
		panic("expected 'fill error: lexeme too long'")
	}

	// Fails, invalid input.
	s = "?#!*"
	if test(s) != lexError {
		panic("expected 'error'")
	}

	fmt.Println("OK")
}
