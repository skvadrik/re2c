// re2zig $INPUT -o $OUTPUT --loop-switch --computed-continue --no-generation-date --no-version

const std = @import("std");

const State = struct {};

fn lex(yyinput: [:0]const u8) bool {
    var yycursor: u32 = 0;
/*!re2c
        re2c:yyfill:enable = 0;

        [a-z]+ { return true; }
        *      { return false; }
    */
}

test {
    _ = State{};
    try std.testing.expect(lex("abc"));
    try std.testing.expect(!lex("123"));
}
