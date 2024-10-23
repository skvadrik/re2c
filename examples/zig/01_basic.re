// re2zig $INPUT -o $OUTPUT

const std = @import("std");

fn lex(yyinput: [:0]const u8) bool {
    var yycursor: u32 = 0;
    %{
        re2c:yyfill:enable = 0;

        [1-9][0-9]* { return true; }
        *           { return false; }
    %}
}

test {
    try std.testing.expect(lex("1234"));
}
