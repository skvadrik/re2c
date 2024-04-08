// re2v $INPUT -o $OUTPUT

// Expects a null-terminated string.
fn lex(str string) int {
    mut cur, mut mar := 0, 0
    lim := str.len - 1 // lim points at the terminating null
    mut count := 0

loop: /*!re2c
    re2c:eof = 0;
    re2c:define:YYCTYPE    = u8;
    re2c:define:YYPEEK     = "str[cur]";
    re2c:define:YYSKIP     = "cur += 1";
    re2c:define:YYBACKUP   = "mar = cur";
    re2c:define:YYRESTORE  = "cur = mar";
    re2c:define:YYLESSTHAN = "lim <= cur";
    re2c:yyfill:enable = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { return -1 }
    $    { return count }
    str  { count += 1; unsafe { goto loop } }
    [ ]+ { unsafe { goto loop } }

    */
}

fn main() {
    assert lex("\0") == 0
    assert lex("'qu\0tes' 'are' 'fine: \\'' \0") == 3
    assert lex("'unterminated\\'\0") == -1
}
