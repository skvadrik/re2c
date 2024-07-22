// re2zig $INPUT -o $OUTPUT

const std = @import("std");

// Expects a null-terminated string.
fn lex(yyinput: [:0]const u8) i32 {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    const yylimit: usize = yyinput.len; // points at the terminating null
    var count: i32 = 0;

    loop: while (true) {
        %{
            re2c:yyfill:enable = 0;
            re2c:eof = 0;

            str = ['] ([^'\\] | [\\][^])* ['];

            *    { return -1; }
            $    { return count; }
            str  { count += 1; continue :loop; }
            [ ]+ { continue :loop; }
        %}
    }
}

test {
    try std.testing.expectEqual(lex(""), 0);
    try std.testing.expectEqual(lex("'qu\x00tes' 'are' 'fine: \\'' "), 3);
    try std.testing.expectEqual(lex("'unterminated\\'"), -1);
}
