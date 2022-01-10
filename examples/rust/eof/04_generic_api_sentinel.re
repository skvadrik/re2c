// re2rust $INPUT -o $OUTPUT

// Expect a string without terminating null.
fn lex(s: &[u8]) -> isize {
    let mut count = 0;
    let mut cur = 0;
    let lim = s.len();

    'lex: loop {/*!re2c
        re2c:define:YYCTYPE = u8;
        re2c:define:YYPEEK  = "if cur < lim {*s.get_unchecked(cur)} else {0}";
        re2c:define:YYSKIP  = "cur += 1;";
        re2c:define:YYFILL  = "{ return -1; }";
        re2c:yyfill:enable = 0;

        *      { return -1; }
        [\x00] { return count; }
        [a-z]+ { count += 1; continue 'lex; }
        [ ]+   { continue 'lex; }
    */}
}

fn main() {
    assert_eq!(lex(b""), 0);
    assert_eq!(lex(b"one two three "), 3);
    assert_eq!(lex(b"f0ur"), -1);
}
