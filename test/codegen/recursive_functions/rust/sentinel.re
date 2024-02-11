// re2rust $INPUT -o $OUTPUT --recursive-functions -i

struct State<'a> {
    str: &'a [u8],
    cur: usize,
    count: i32,
}

/*!re2c
    re2c:define:YYFN    = ["lex;i32", "_st;&mut State"];
    re2c:define:YYCTYPE = u8;
    re2c:define:YYPEEK  = "*_st.str.get_unchecked(_st.cur)";
    re2c:define:YYSKIP  = "_st.cur += 1;";
    re2c:yyfill:enable  = 0;

    *      { return -1; }
    [\x00] { return _st.count; }
    [a-z]+ { _st.count += 1; return lex(_st); }
    [ ]+   { return lex(_st); }
*/

fn main() {
    assert_eq!(lex(&mut State{str: b"\0", cur: 0, count: 0}), 0);
    assert_eq!(lex(&mut State{str: b"one two three\0", cur: 0, count: 0}), 3);
    assert_eq!(lex(&mut State{str: b"f0ur\0", cur: 0, count: 0}), -1);
}
