//go:generate re2go $INPUT -o $OUTPUT -i
package main

func lex(yyinput string) {
	var yycursor int
	/*!re2c
		re2c:api = default;
		re2c:define:YYCTYPE = byte;
		re2c:yyfill:enable = 0;

		number = [1-9][0-9]*;

		number { return }
		*      { panic("error!") }
	*/
}

func main() {
	lex("1234\x00")
}
