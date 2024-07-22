// re2zig $INPUT -o $OUTPUT --recursive-functions

const std = @import("std");

const State = struct {
    str: [:0]const u8,
    cur: u32,
};

/*!re2c
    re2c:api = custom;
    re2c:define:YYFN = ["lex;bool", "st;*State"];
    re2c:define:YYPEEK = "st.str[st.cur]";
    re2c:define:YYSKIP = "st.cur += 1;";
    re2c:yyfill:enable = 0;

    number = [1-9][0-9]*;

    number { _ = st; return true; }
    *      { _ = st; return false; }
*/

test {
    var st = State{.str = "1234", .cur = 0};
    try std.testing.expect(lex(&st));
}
