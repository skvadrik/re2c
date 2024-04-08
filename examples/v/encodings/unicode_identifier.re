// re2v $INPUT -o $OUTPUT --utf8 -si

/*!include:re2c "unicode_categories.re" */

fn lex(str string) int {
    mut cur, mut mar := 0, 0
    /*!re2c
        re2c:yyfill:enable    = 0;
        re2c:define:YYCTYPE   = u8;
        re2c:define:YYPEEK    = "str[cur]";
        re2c:define:YYSKIP    = "cur += 1";
        re2c:define:YYBACKUP  = "mar = cur";
        re2c:define:YYRESTORE = "cur = mar";

        // Simplified "Unicode Identifier and Pattern Syntax"
        // (see https://unicode.org/reports/tr31)
        id_start    = L | Nl | [$_];
        id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
        identifier  = id_start id_continue*;

        identifier { return 0 }
        *          { return 1 }
    */
}

fn main() {
    if lex("_Ыдентификатор\0") != 0 {
        panic("error")
    }
}
