//go:generate re2go $INPUT -o $OUTPUT -i
package main

func lex(str string) {
	var cursor int
	/*!re2c
		re2c:define:YYCTYPE = byte;
		re2c:define:YYPEEK = "str[cursor]";
		re2c:define:YYSKIP = "cursor += 1";
		re2c:yyfill:enable = 0;

		number = [1-9][0-9]*;

		number { return }
		*      { panic("error!") }
	*/
}

func main() {
	lex("1234\x00")
}
