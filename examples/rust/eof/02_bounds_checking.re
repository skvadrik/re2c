// re2rust $INPUT -o $OUTPUT

/*!max:re2c*/

fn lex(s: &[u8]) -> isize {
    let mut count = 0;
    let mut cursor = 0;
    let limit = s.len() + YYMAXFILL;

    // Copy string to a buffer and add YYMAXFILL zero padding.
    let mut buf = Vec::with_capacity(limit);
    buf.extend(s.iter());
    buf.extend(vec![0; YYMAXFILL]);

    'lex: loop {/*!re2c
        re2c:define:YYCTYPE = u8;
        re2c:define:YYPEEK = "*buf.get_unchecked(cursor)";
        re2c:define:YYSKIP = "cursor += 1;";
        re2c:define:YYFILL = "return -1;";
        re2c:define:YYLESSTHAN = "cursor + @@ > limit";

        *                           { return -1; }
        [\x00]                      { return if cursor == s.len() + 1 { count } else { -1 }; }
        ['] ([^'\\] | [\\][^])* ['] { count += 1; continue 'lex; }
        [ ]+                        { continue 'lex; }
    */}
}

fn main() {
    assert_eq!(lex(b""), 0);
    assert_eq!(lex(b"'qu\0tes' 'are' 'fine: \\'' "), 3);
    assert_eq!(lex(b"'unterminated\\'"), -1);
}
