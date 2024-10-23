// re2rust $INPUT -o $OUTPUT --api simple

fn lex(yyinput: &[u8]) -> isize {
    // The input must be null-terminated, otherwise the function has UB.
    assert_eq!(yyinput.last(), Some(&0));

    let mut yycursor = 0;
    let mut count = 0;

    'lex: loop { /*!re2c
        re2c:YYCTYPE = u8;
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
