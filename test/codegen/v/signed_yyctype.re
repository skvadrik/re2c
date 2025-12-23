// re2v $INPUT -o $OUTPUT -i

/*!rules:re2c
    re2c:api = generic;
    re2c:YYSKIP = "cur +=1;";
    re2c:yyfill:enable = 0;

    [\xff] { return true }
    *      { return false }
*/

fn lex_unsigned(str []u8) bool {
    mut cur := 0
    /*!use:re2c
        re2c:YYCTYPE = "u8";
        re2c:YYPEEK = "str[cur]";
    */
}

fn lex_signed(str []u8) bool {
    mut cur := 0
    /*!use:re2c
        re2c:YYCTYPE = "i8"; // should be unsigned!
        re2c:YYPEEK = "i8(str[cur])";
    */
}

fn main() {
    s := [u8(0xff)]
    assert lex_unsigned(s)
    assert !lex_signed(s) // error - lexer works incorrectly
}
