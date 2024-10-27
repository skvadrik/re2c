// re2rust $INPUT -o $OUTPUT --api simple

fn lex(yyinput: &[u8]) -> isize {
    // The input must be null-terminated, otherwise the function has UB.
    assert_eq!(yyinput.last(), Some(&0));

    let (mut yycursor, mut yymarker) = (0, 0);
    let yylimit = yyinput.len() - 1; // null-terminator not included
    let mut count = 0;

    'lex: loop { /*!re2c
        re2c:YYCTYPE = u8;
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
    assert_eq!(lex(b"\0"), 0);
    assert_eq!(lex(b"'qu\0tes' 'are' 'fine: \\'' \0"), 3);
    assert_eq!(lex(b"'unterminated\\'\0"), -1);
}
