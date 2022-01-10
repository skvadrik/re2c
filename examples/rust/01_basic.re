// re2rust $INPUT -o $OUTPUT

fn lex(s: &[u8]) -> bool {                            // Rust code
    let mut cursor = 0;                               //
/*!re2c
    re2c:define:YYCTYPE = u8;                         //
    re2c:define:YYPEEK = "*s.get_unchecked(cursor)";  // configurations
    re2c:define:YYSKIP = "cursor += 1;";              //
    re2c:yyfill:enable = 0;                           //

    alpha = [a-zA-Z];                                 // named definitions
    ident = alpha (alpha | [0-9])*;                   //

    ident  { return true; }                           // rules
    *      { return false; }                          //
*/
}                                                     //
                                                      //
fn main() {                                           // Rust code
    assert!(lex(b"qwerty42\0"));                      //
}                                                     //
