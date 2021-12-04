// re2rust $INPUT -o $OUTPUT

unsafe fn lex(s: &[u8]) -> bool {                     // Rust code
    let mut cursor : usize = 0;                       //
                                                      //
/*!re2c
    re2c:define:YYCTYPE = u8;                         //
    re2c:define:YYPEEK = "*s.get_unchecked(cursor)";  //
    re2c:define:YYSKIP = "cursor += 1;";              // configurations
    re2c:yyfill:enable = 0;                           //
                                                      //
    alpha = [a-zA-Z];                                 // named definitions
    ident = alpha (alpha | [0-9])*;                   //
                                                      //
    ident  { return true; }                           // rules
    *      { return false; }                          //
*/
}                                                     //
                                                      //
fn main() {                                           // Rust code
    unsafe {                                          //
        if !lex(("qwerty42\0").as_bytes()) {          //
            panic!("error");                          //
        }                                             //
    }                                                 //
}                                                     //
