// re2rust $INPUT -o $OUTPUT

/*!include:re2c "definitions.rs" */

fn lex(yyinput: &[u8]) -> Num {
    assert_eq!(yyinput.last(), Some(&0)); // expect null-terminated input

    let mut yycursor = 0;
    let mut yymarker = 0;
    /*!re2c
        re2c:api = default;
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = u8;

        *      { return Num::NaN; }
        number { return Num::Int; }
        !include "extra_rules.re.inc";
    */
}

fn main() {
    assert_eq!(lex(b"123\0"), Num::Int);
    assert_eq!(lex(b"123.4567\0"), Num::Float);
}
