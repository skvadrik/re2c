// re2rust $INPUT -o $OUTPUT

// Expect a null-terminated string.
fn lex(s: &[u8]) -> isize {
    let mut cur = 0;
    let mut count = 0;

    'lex: loop {/*!re2c
        re2c:define:YYCTYPE = u8;
        re2c:define:YYPEEK  = "*s.get_unchecked(cur)";
        re2c:define:YYSKIP  = "cur += 1;";
        re2c:yyfill:enable = 0;

        *      { return -1; }
        [\x00] { return count; }
        [a-z]+ { count += 1; continue 'lex; }
        [ ]+   { continue 'lex; }
    */}
}

fn main() {
    assert_eq!(lex(b"\x00"), 0);
    assert_eq!(lex(b"one two three\x00"), 3);
    assert_eq!(lex(b"f0ur\x00"), -1);
}
