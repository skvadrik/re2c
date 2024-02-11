// re2rust $INPUT -o $OUTPUT --recursive-functions -i

/*!max:re2c*/

struct State {
    buf: Vec<u8>,
    cur: usize,
    lim: usize,
    count: i32,
}

/*!re2c
    re2c:define:YYFN       = ["lex;i32", "_st;&mut State"];
    re2c:define:YYCTYPE    = u8;
    re2c:define:YYPEEK     = "*_st.buf.get_unchecked(_st.cur)";
    re2c:define:YYSKIP     = "_st.cur += 1;";
    re2c:define:YYLESSTHAN = "_st.cur + @@ > _st.lim";
    re2c:define:YYFILL     = "return -1;";

    *                           { return -1; }
    [\x00]                      { return if _st.cur + YYMAXFILL - 1 == _st.lim { _st.count } else { -1 }; }
    ['] ([^'\\] | [\\][^])* ['] { _st.count += 1; return lex(_st); }
    [ ]+                        { return lex(_st); }
*/

fn test(s: &[u8]) -> i32 {
    let lim = s.len() + YYMAXFILL;

    // Copy string to a buffer and add YYMAXFILL zero padding.
    let mut buf = Vec::with_capacity(lim);
    buf.extend(s.iter());
    buf.extend(vec![0; YYMAXFILL]);

    let mut st = State{buf: buf, cur: 0, lim: lim, count: 0};
    return lex(&mut st);
}

fn main() {
    assert_eq!(test(b""), 0);
    assert_eq!(test(b"'qu\0tes' 'are' 'fine: \\'' "), 3);
    assert_eq!(test(b"'unterminated\\'"), -1);
}
