//go:generate re2go $INPUT -o $OUTPUT --recursive-functions -i
package main

/*!re2c
    re2c:define:YYFN = ["lex", "str;string", "cur;int"];
    re2c:define:YYCTYPE = byte;
    re2c:define:YYPEEK = "str[cur]";
    re2c:define:YYSKIP = "cur += 1";
    re2c:yyfill:enable = 0;
    re2c:flags:nested-ifs = 1;

    number = [1-9][0-9]*;

    number { return }
    *      { panic("error!"); }
*/

func main() {
    lex("1234\x00", 0)
}
