package main

type YYCTYPE byte
type Input struct {
	data   []YYCTYPE
	cursor int
	marker int
}

func peek(in *Input) func() YYCTYPE {
	return func() YYCTYPE {
		return in.data[in.cursor]
	}
}

func skip(in *Input) func() {
	return func() {
		in.cursor++
	}
}

func backup(in *Input) func() {
	return func() {
		in.marker = in.cursor
	}
}

func restore(in *Input) func() {
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
	re2c:flags:input = custom;
	re2c:yyfill:enable = 0;

	end = [\x00];

	* {
		return -1
	}

	[0-9]+ end {
		return 1
	}
	*/
}

func main() {
	if Lex("123\000") != 1 {
		panic("expected 123")
	}
}
