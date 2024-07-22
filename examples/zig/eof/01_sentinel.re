// re2zig $INPUT -o $OUTPUT

const std = @import("std");

// Expects a null-terminated string.
fn lex(yyinput: [:0]const u8) i32 {
    var yycursor: u32 = 0;
    var count: i32 = 0;

    loop: while (true) {
        %{
            re2c:yyfill:enable = 0;

            *      { return -1; }
            [\x00] { return count; }
            [a-z]+ { count += 1; continue :loop; }
            [ ]+   { continue :loop; }
        %}
    }
}

test {
    try std.testing.expectEqual(lex(""), 0);
    try std.testing.expectEqual(lex("one two three"), 3);
    try std.testing.expectEqual(lex("f0ur"), -1);
}
