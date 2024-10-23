// re2v $INPUT -o $OUTPUT

// Returns "fake" terminating null if cursor has reached limit.
fn peek(str string, cur int) u8 {
    return if cur >= str.len { u8(0) } /* fake null */ else { return str[cur] }
}

// Expects a string without terminating null.
fn lex(str string) int {
    mut cur := 0
    mut count := 0

loop: /*!re2c
    re2c:api = generic;
    re2c:yyfill:enable = 0;
    re2c:YYPEEK = "peek(str, cur)";
    re2c:YYSKIP = "cur += 1";

    *      { return -1 }
    [\x00] { return count }
    [a-z]+ { count += 1; unsafe { goto loop } }
    [ ]+   { unsafe { goto loop } }

    */
}

fn main() {
    assert lex("") == 0
    assert lex("one two three") == 3
    assert lex("f0ur") == -1
}
