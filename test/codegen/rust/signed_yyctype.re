// re2rust $INPUT -o $OUTPUT --api simple

/*!rules:re2c
    re2c:yyfill:enable = 0;

    [\xff] { return true; }
    *      { return false; }
*/

fn lex_unsigned(yyinput: &[u8]) -> bool {
    let mut yycursor = 0;
    /*!use:re2c
        re2c:YYCTYPE = u8;
    */
}

#[allow(overflowing_literals)]
fn lex_signed(yyinput: &[u8]) -> bool {
    let mut yycursor = 0;
    /*!use:re2c
        re2c:YYCTYPE = i8; // should be signed!
        re2c:yych:conversion = 1;
    */
}

fn main() {
    assert!(!lex_unsigned(b"a\0")); // ok, 'a' should not match
    assert!(lex_signed(b"a\0")); // error, 'a' does match
}
