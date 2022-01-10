// re2rust $INPUT -o $OUTPUT

// Expect a string without terminating null.
fn lex(s: &[u8]) -> isize {
    let (mut cur, mut mar) = (0, 0);
    let lim = s.len();
    let mut count = 0;

    'lex: loop {/*!re2c
        re2c:define:YYCTYPE    = u8;
        re2c:define:YYPEEK     = "if cur < lim {*s.get_unchecked(cur)} else {0}";
        re2c:define:YYSKIP     = "cur += 1;";
        re2c:define:YYBACKUP   = "mar = cur;";
        re2c:define:YYRESTORE  = "cur = mar;";
        re2c:define:YYLESSTHAN = "cur >= lim";
        re2c:yyfill:enable = 0;
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return count; }
        str  { count += 1; continue 'lex; }
        [ ]+ { continue 'lex; }
    */}
}

fn main() {
    assert_eq!(lex(b""), 0);
    assert_eq!(lex(b"'qu\0tes' 'are' 'fine: \\'' "), 3);
    assert_eq!(lex(b"'unterminated\\'"), -1);
}
