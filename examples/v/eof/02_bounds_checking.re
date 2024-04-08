// re2v $INPUT -o $OUTPUT

/*!max:re2c*/

// Expects yymaxfill-padded string.
fn lex(str string) int {
    // Pad string with yymaxfill zeroes at the end.
    mut buf := []u8{len: str.len + yymaxfill}
    copy(mut &buf, str.bytes())

    mut cur := 0
    lim := buf.len
    mut count := 0

loop: /*!re2c
    re2c:define:YYCTYPE    = u8;
    re2c:define:YYPEEK     = "buf[cur]";
    re2c:define:YYSKIP     = "cur += 1";
    re2c:define:YYLESSTHAN = "lim - cur < @@";
    re2c:define:YYFILL     = "return -1";

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        // Check that it is the sentinel, not some unexpected null.
        if cur - 1 == str.len { return count } else { return -1 }
    }
    str  { count += 1; unsafe { goto loop } }
    [ ]+ { unsafe { goto loop } }
    *    { return -1 }

    */
}

fn main() {
    assert lex("") == 0
    assert lex("'qu\0tes' 'are' 'fine: \\'' ") == 3
    assert lex("'unterminated\\'") == -1
    assert lex("'unexpected \00 null\\'") == -1
}
