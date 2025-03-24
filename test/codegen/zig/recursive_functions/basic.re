// re2zig $INPUT -o $OUTPUT --recursive-functions

const std = @import("std");

const State = struct {
    str: [:0]const u8,
    cur: u32,
};

const SyntaxError = error {
    UnexpectedCharacter
};

/*!re2c
    re2c:api = custom;
    re2c:define:YYFN = ["lex;void", "st;*State"];
    re2c:define:YYPEEK = "st.str[st.cur]";
    re2c:define:YYSKIP = "st.cur += 1;";
    re2c:yyfill:enable = 0;
    re2c:yyfn:throw = "SyntaxError";

    number = [1-9][0-9]*;

    number { _ = st; return; }
    *      { _ = st; return SyntaxError.UnexpectedCharacter; }
*/

test {
    var st = State{.str = "1234", .cur = 0};
    try lex(&st);
}
