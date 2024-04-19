//go:generate re2go $INPUT -o $OUTPUT 
package main

func Lex(str string) int {
	var cursor int

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";

	* {
		var s0, s1 string
		{s0 = "}}"}
		{s1 = "}}}"}
		{s0 = `}}`}
		{s1 = `}}}`}
		var c0, c1 rune
		{c0 = '\''}
		{c1 = '\x7F'}
		{c0 = '}'}
		{c1 = '\t'}
		{c0 = '\u7FFF'}
		{c1 = 'ы'}
		{c0 = '\a'}
		{c1 = '\255'}
		{c0 = '\000'}
		{c1 = '\U0000FFFF'}
		if c0 == c1 || c0 != rune(yych) || s0 == s1 {
			return 1;
		}
		return 0
	}
	*/
}

func main() {
	if Lex("xxx") != 0 {
		panic("expected 0")
	}
}
