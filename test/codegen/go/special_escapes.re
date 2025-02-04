//go:generate re2go $INPUT -o $OUTPUT -i --api simple
package main

func lex(yyinput string) {
	var yycursor, yymarker int
	/*!re2c
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;

		"\a\b\f\n\r\t\v\\'\"" { return }
		* {
			_ = []rune{'\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\', '\''}
			_ = "\""
			panic("error!")
		}
	*/
}

func main() {
	lex("\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"\x00")
}
