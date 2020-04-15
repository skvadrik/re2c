/*!re2c
re2c:flags:input = custom;
*/

package main

import "fmt"
import "os"

var SIZE int = 10

type YYCTYPE byte
type Input struct {
	file   *os.File
	data   []byte
	cursor int
	marker int
	token  int
	limit  int
}

func peek(input *Input) func() YYCTYPE {
	in := input
	return func() YYCTYPE {
		return YYCTYPE(in.data[in.cursor])
	}
}

func skip(input *Input) func() {
	in := input
	return func() {
		in.cursor++
	}
}

func backup(input *Input) func() {
	in := input
	return func() {
		in.marker = in.cursor
	}
}

func restore(input *Input) func() {
	in := input
	return func() {
		in.cursor = in.marker
	}
}

func fill(input *Input) func() int {
	in := input
	return func() int {
		if in.limit < SIZE {
			return 1
		}

		copy(in.data[0:], in.data[in.token:in.cursor])

		in.cursor = in.cursor - in.token
		in.marker = in.marker - in.token
		in.limit = in.limit - in.token
		in.token = 0

		n, _ := in.file.Read(in.data[in.limit:SIZE])
		in.limit = in.limit + n
		in.data[in.limit] = 0
		fmt.Printf("fill: %v '%s'\n", input.data[:input.limit+1], string(input.data[:input.limit]))

		if n == 0 {
			return 1
		}
		return 0
	}
}

func lessthan(input *Input) func(int) bool {
	in := input
	return func(n int) bool {
		return in.limit-in.cursor < n
	}
}

func Lex(input *Input) int {
	YYPEEK := peek(input)
	YYSKIP := skip(input)
	YYBACKUP := backup(input)
	YYRESTORE := restore(input)
	YYFILL := fill(input)
	YYLESSTHAN := lessthan(input)
	input.token = input.cursor

	/*!re2c
	re2c:eof = 0;

	* {
		fmt.Println("error")
		return -1
	}

	$ {
		fmt.Println("end")
		return 0
	}

	[0-9]+ {
		fmt.Printf("number: %v\n", string(input.data[input.token:input.cursor]))
		return 1
	}

	[0-9]+ [.] [0-9]+ {
		fmt.Println("number-2")
		return 2
	}

	[ \t\r\n]+ {
		return 3
	}
	*/
}

func main() {
	tmpfile := "input.txt"
	f, _ := os.Create(tmpfile)
	f.WriteString("     123456789     \n")
	f.Seek(0, 0)

	input := &Input{
		file:   f,
		data:   make([]byte, SIZE+1),
		cursor: SIZE,
		marker: SIZE,
		token:  SIZE,
		limit:  SIZE,
	}

	result := 9999
	for result > 0 {
		result = Lex(input)
	}

	f.Close()
	os.Remove(tmpfile)
}
