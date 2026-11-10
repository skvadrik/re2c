//go:generate re2go $INPUT -o $OUTPUT --recursive-functions -b -i
package main

import "fmt"

/*!re2c
    re2c:define:YYFN = ["lex;int", "str;string", "cur;int"];
    re2c:define:YYCTYPE = byte;
    re2c:define:YYPEEK = "str[cur]";
    re2c:define:YYSKIP = "cur += 1";
    re2c:yyfill:enable = 0;

    number = [1-9][0-9]*;
    word   = [a-z]+;

    number { return 0 }
    word   { return 1 }
    *      { return 2 }
*/

func main() {
	if lex("123\x00", 0) != 0 {
		panic("bad number")
	}
	if lex("abc\x00", 0) != 1 {
		panic("bad word")
	}
	if lex("??\x00", 0) != 2 {
		panic("bad error case")
	}
	fmt.Println("ok")
}
