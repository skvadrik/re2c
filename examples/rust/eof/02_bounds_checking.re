// re2rust $INPUT -o $OUTPUT

/*!max:re2c*/

fn lex(s: &[u8]) -> isize {
    let mut count = 0;
    let mut cur = 0;
    let lim = s.len() + YYMAXFILL;

    // Copy string to a buffer and add YYMAXFILL zero padding.
    let mut buf = Vec::with_capacity(lim);
    buf.extend(s.iter());
    buf.extend(vec![0; YYMAXFILL]);

    'lex: loop {/*!re2c
        re2c:define:YYCTYPE    = u8;
        re2c:define:YYPEEK     = "*buf.get_unchecked(cur)";
        re2c:define:YYSKIP     = "cur += 1;";
        re2c:define:YYFILL     = "return -1;";
        re2c:define:YYLESSTHAN = "cur + @@ > lim";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return if cur == s.len() + 1 { count } else { -1 }
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
