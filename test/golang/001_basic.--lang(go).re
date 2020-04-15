/*!re2c
	re2c:flags:input = custom;
*/

package main

import "fmt"

type YYCTYPE byte
type Input struct {
	data  []YYCTYPE
	cursor int
	marker int
}

func peek(input *Input) func() YYCTYPE {
	in := input
	return func() YYCTYPE {
		return in.data[in.cursor]
	}
}

func skip(input *Input) func() {
	in := input
	return func() {
		in.cursor++
	}
}

func Lex(input *Input) int {
	YYPEEK := peek(input)
	YYSKIP := skip(input)

	/*!re2c
	re2c:yyfill:enable = 0;

	* {
		fmt.Println("error")
		return -1
	}

	[\x00] {
		fmt.Println("end")
		return 0
	}

	[0-9]+ {
		fmt.Println("number")
		return 1
	}

	[a-zA-Z_-]+ {
		fmt.Println("string")
		return 2
	}

	[ \t]+ {
		fmt.Println("space")
		return 3
	}
	*/
}

func main() {
	input := &Input{
		data:  []YYCTYPE("1024 fourty-two\x00"),
		cursor: 0,
	}

	result := 9999
	for result > 0 {
		result = Lex(input)
	}
}
