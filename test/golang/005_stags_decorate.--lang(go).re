package main

type YYCTYPE byte
type Input struct {
	data   []YYCTYPE
	cursor int
	marker int
	/*!stags:re2c
		format = "@@ int";
		separator = "\n\t";
	*/
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

func stagp(in *Input) func(tag *int) {
	return func(tag *int) {
		*tag = in.cursor
	}
}

func stagn(tag *int) {
	*tag = -1
}

func Lex(str string) (int, int, int) {
	in := &Input{
		data:   []YYCTYPE(str),
		cursor: 0,
	}
	YYPEEK := peek(in)
	YYSKIP := skip(in)
	YYBACKUP := backup(in)
	YYRESTORE := restore(in)
	YYSTAGP := stagp(in)
	YYSTAGN := stagn
	var a, b, c *int

	/*!re2c
	re2c:flags:input = custom;
	re2c:flags:tags = 1;
	re2c:yyfill:enable = 0;
	re2c:tags:expression = "&in.@@";

	end = [\x00];

	* {
		return -2, -2, -2
	}

	@a [a]+ @b [b] @c [c]+ end {
		return *a, *b, *c
	}

	(@a [a]+ | @b [b]+ | @c [c]+) end {
		return *a, *b, *c
	}

	(@a [a] (@b [b])? @c [c])* end {
		return *a, *b, *c
	}
	*/
}

func main() {
	if a, b, c := Lex("aabcc\000"); !(a == 0 && b == 2 && c == 3) {
		panic("expected 0,2,3")
	}
	if a, b, c := Lex("aaa\000"); !(a == 0 && b == -1 && c == -1) {
		panic("expected 0,-1,-1")
	}
	if a, b, c := Lex("acabc\000"); !(a == 2 && b == 3 && c == 4) {
		panic("expected 2,3,4")
	}
	if a, b, c := Lex("abcac\000"); !(a == 3 && b == -1 && c == 4) {
		panic("expected 3,-1,4")
	}
	if a, b, c := Lex("ab\000"); !(a == -2 && b == -2 && c == -2) {
		panic("expected -2,-2,-2")
	}
}
