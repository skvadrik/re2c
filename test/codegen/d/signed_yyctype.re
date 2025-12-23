// re2d $INPUT -o $OUTPUT -i
module main;

/*!rules:re2c
    re2c:yyfill:enable = 0;

    [\xff] { return true; }
    *      { return false; }
*/

private bool lex_unsigned(const(char)* yycursor) {
    /*!use:re2c
        re2c:YYCTYPE = char;
    */
}

private bool lex_signed(const(char)* yycursor) {
    /*!use:re2c
        re2c:YYCTYPE = byte; // should be unsigned!
    */
}

void main() {
    assert(lex_unsigned("\xff"));
    assert(!lex_signed("\xff")); // error - lexer is working incorrectly
}
