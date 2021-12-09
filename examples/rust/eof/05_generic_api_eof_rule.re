// re2rust $INPUT -o $OUTPUT

// Expect a string without terminating null.
fn lex(s: &[u8]) -> isize {
    let mut count = 0;
    let mut cursor = 0;
    let mut marker = 0;
    let limit = s.len();

    'lex: loop {/*!re2c
        re2c:define:YYCTYPE = u8;
        re2c:define:YYPEEK = "if cursor < limit { *s.get_unchecked(cursor) } else { 0 }";
        re2c:define:YYSKIP = "cursor += 1;";
        re2c:define:YYBACKUP = "marker = cursor;";
        re2c:define:YYRESTORE = "cursor = marker;";
        re2c:define:YYLESSTHAN = "cursor >= limit";
        re2c:yyfill:enable = 0;
        re2c:eof = 0;

        *                           { return -1; }
        $                           { return count; }
        ['] ([^'\\] | [\\][^])* ['] { count += 1; continue 'lex; }
        [ ]+                        { continue 'lex; }
    */}
}

fn main() {
    assert_eq!(lex(b""), 0);
    assert_eq!(lex(b"'qu\0tes' 'are' 'fine: \\'' "), 3);
    assert_eq!(lex(b"'unterminated\\'"), -1);
}
