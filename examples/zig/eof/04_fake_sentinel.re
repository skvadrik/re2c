// re2zig $INPUT -o $OUTPUT

const std = @import("std");

// Expects a string without terminating null.
fn lex(str: []const u8) i32 {
    var cur: usize = 0;
    var count: i32 = 0;

    loop: while (true) {
        %{
            re2c:api = generic;
            re2c:yyfill:enable = 0;
            // YYPEEK returns "fake" terminating null if cursor has reached limit.
            re2c:YYPEEK = "if (cur >= str.len) 0 else str[cur]";
            re2c:YYSKIP = "cur += 1;";

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
