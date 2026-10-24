//go:generate re2go $INPUT -o $OUTPUT -s -i --vectorize-linear
package main

func Lex(yyinput string) int {
	yycursor, yymarker := 0, 0
	_ = yymarker

	/*!re2c
	re2c:api = simple;
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;

	end = [\x00];

	* { return -1 }
	"SELECT" end { return 1 }
	*/
}

func main() {
	if Lex("SELECT\000") != 1 { panic("SELECT") }
	if Lex("UNKNOWN\000") != -1 { panic("UNKNOWN") }
	for i := 0; i < len("SELECT"); i++ {
		if Lex("SELECT"[:i]+"\000") != -1 { panic("prefix") }
	}
}
