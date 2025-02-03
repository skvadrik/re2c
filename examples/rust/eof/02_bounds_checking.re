// re2rust $INPUT -o $OUTPUT --api simple

/*!max:re2c*/

fn lex(s: &[u8]) -> isize {
    let mut count = 0;
    let mut yycursor = 0;
    let yylimit = s.len() + YYMAXFILL;

    // Copy string to a buffer and add YYMAXFILL zero padding.
    let mut yyinput = Vec::with_capacity(yylimit);
    yyinput.extend_from_slice(s);
    yyinput.extend([0 as u8; YYMAXFILL]);

    'lex: loop { /*!re2c
        re2c:YYCTYPE = u8;
        re2c:YYFILL = "return -1;";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return if yycursor == s.len() + 1 { count } else { -1 }
        }
        str  { count += 1; continue 'lex; }
        [ ]+ { continue 'lex; }
        *    { return -1; }
    */}
}

fn main() {
    assert_eq!(lex(b""), 0);
    assert_eq!(lex(b"'qu\0tes' 'are' 'fine: \\'' "), 3);
    assert_eq!(lex(b"'unterminated\\'"), -1);
    assert_eq!(lex(b"'unexpected \0 null"), -1);
}
