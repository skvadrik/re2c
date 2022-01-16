// re2rust $INPUT -o $OUTPUT

/*!include:re2c "definitions.rs" */

fn lex(str: &[u8]) -> Num {
    let mut cur = 0;
    let mut mar = 0;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE   = u8;
        re2c:define:YYPEEK    = "*str.get_unchecked(cur)";
        re2c:define:YYSKIP    = "cur += 1;";
        re2c:define:YYBACKUP  = "mar = cur;";
        re2c:define:YYRESTORE = "cur = mar;";

        *      { return Num::NaN; }
        number { return Num::Int; }
        !include "extra_rules.re.inc";
    */
}

fn main() {
    assert_eq!(lex(b"123\0"), Num::Int);
    assert_eq!(lex(b"123.4567\0"), Num::Float);
}
