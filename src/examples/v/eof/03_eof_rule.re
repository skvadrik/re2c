// re2v $INPUT -o $OUTPUT

// Expects a null-terminated string.
fn lex(yyinput string) int {
    mut yycursor, mut yymarker := 0, 0
    yylimit := yyinput.len - 1 // yylimit points at the terminating null
    mut count := 0

loop: /*!re2c
    re2c:eof = 0;
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
