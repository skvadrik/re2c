//go:generate re2go $INPUT -o $OUTPUT -i --api simple
package main

func lex(yyinput string) {
	var yycursor int
	/*!re2c
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;

		[1-9][0-9]* { return }
		*           { panic("error!") }
	*/
}

func main() {
	lex("1234\x00")
}
