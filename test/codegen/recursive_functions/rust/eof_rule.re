// re2rust $INPUT -o $OUTPUT --recursive-functions

struct State<'a> {
    str: &'a [u8],
    lim: usize,
    cur: usize,
    mar: usize,
    count: isize
}

// Expect a null-terminated string.
fn lex(str: &[u8]) -> isize {
    let mut st = State {
        str: str,
        lim: str.len() - 1, // null-terminator not included
        cur: 0,
        mar: 0,
        count: 0
    };
    return lex_loop(&mut st);
}

/*!re2c
    re2c:define:YYFN       = ["lex_loop;isize", "_st;&mut State"];
    re2c:define:YYCTYPE    = u8;
    re2c:define:YYPEEK     = "*_st.str.get_unchecked(_st.cur)";
    re2c:define:YYSKIP     = "_st.cur += 1;";
    re2c:define:YYBACKUP   = "_st.mar = _st.cur;";
    re2c:define:YYRESTORE  = "_st.cur = _st.mar;";
    re2c:define:YYLESSTHAN = "_st.cur >= _st.lim";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { return -1; }
    $    { return _st.count; }
    str  { _st.count += 1; return lex_loop(_st); }
    [ ]+ { return lex_loop(_st); }
*/

fn main() {
    assert_eq!(lex(b"\0"), 0);
    assert_eq!(lex(b"'qu\0tes' 'are' 'fine: \\'' \0"), 3);
    assert_eq!(lex(b"'unterminated\\'\0"), -1);
}
