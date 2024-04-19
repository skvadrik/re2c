// re2v $INPUT -o $OUTPUT --recursive-functions

struct State {
    str string
mut:
    cur u32
}

/*!re2c
    re2c:define:YYFN = ["lex", "mut st;State"];
    re2c:define:YYCTYPE = u8;
    re2c:define:YYPEEK = "st.str[st.cur]";
    re2c:define:YYSKIP = "st.cur += 1";
    re2c:yyfill:enable = 0;

    number = [1-9][0-9]*;

    number { return }
    *      { panic("error!") }
*/

fn main() {
    mut st := &State{str: "1234\x00", cur: 0}
    lex(mut st)
}
