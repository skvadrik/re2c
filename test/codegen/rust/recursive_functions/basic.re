// re2rust $INPUT -o $OUTPUT --recursive-functions -i

/*!re2c
    re2c:define:YYCTYPE = u8;
    re2c:define:YYFN    = ["lex", "_str;&[u8]", "_cur;usize;mut"];
    re2c:define:YYPEEK  = "*_str.get_unchecked(_cur)";
    re2c:define:YYSKIP  = "_cur += 1;";
    re2c:yyfill:enable  = 0;

    alpha = [a-zA-Z];
    ident = alpha (alpha | [0-9])*;

    ident { return; }
    *     { panic!("garbage!"); }
*/

fn main() {
    lex(b"qwerty42\0", 0);
}
