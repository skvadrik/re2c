// re2zig $INPUT -o $OUTPUT

const std = @import("std");

%{max %}

fn lex(str: []const u8) !i32 {
    // Create a copy of the input string padded with yymaxfill zeroes at the end.
    var yyinput = try std.testing.allocator.alloc(u8, str.len + yymaxfill);
    defer std.testing.allocator.free(yyinput);
    std.mem.copy(u8, yyinput[0..], str);
    std.mem.copy(u8, yyinput[str.len..], &[_]u8{0} ** yymaxfill); // zero padding

    var yycursor: usize = 0;
    var yylimit: usize = yyinput.len;
    var count: i32 = 0;

    loop: while (true) {
        %{
            re2c:YYFILL = "return -1;";

            str = ['] ([^'\\] | [\\][^])* ['];

            [\x00] {
                // Check that it is the sentinel, not some unexpected null.
                return if (yycursor - 1 == str.len) count else -1;
            }
            str  { count += 1; continue :loop; }
            [ ]+ { continue :loop; }
            *    { return -1; }
        %}
    }
}

test {
    try std.testing.expectEqual(lex(""), 0);
    try std.testing.expectEqual(lex("'qu\x00tes' 'are' 'fine: \\'' "), 3);
    try std.testing.expectEqual(lex("'unterminated\\'"), -1);
    try std.testing.expectEqual(lex("'unexpected \x00 null\\'"), -1);
}
