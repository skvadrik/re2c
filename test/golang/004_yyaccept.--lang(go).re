/*!re2c
	re2c:flags:input = custom;
*/

package main

type YYCTYPE byte
type Input struct {
	data   []YYCTYPE
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

func Lex(str string) int {
	in := &Input{
		data:   []YYCTYPE(str),
		cursor: 0,
	}
	YYPEEK := peek(in)
	YYSKIP := skip(in)
	YYBACKUP := backup(in)
	YYRESTORE := restore(in)

	/*!re2c
	re2c:yyfill:enable = 0;

	end = [\x00];

	* {
		return -1
	}

	"a" {
		return 1
	}

	"abc" {
		return 2
	}

	"abcde" {
		return 3
	}

	"abcdefg" {
		return 4
	}
	*/
}

func main() {
	if Lex("\000") != -1 {
		panic("expected error")
	}
	if Lex("a\000") != 1 {
		panic("expected 'a'")
	}
	if Lex("abc\000") != 2 {
		panic("expected 'abc'")
	}
	if Lex("abcde\000") != 3 {
		panic("expected 'abcde'")
	}
	if Lex("abcdefg\000") != 4 {
		panic("expected 'abcdefg'")
	}
}
