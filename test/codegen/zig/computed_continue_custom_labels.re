// re2zig $INPUT -o $OUTPUT --loop-switch --computed-continue --no-generation-date --no-version

const std = @import("std");

fn lex(yyinput: [:0]const u8) u8 {
    var yycursor: usize = 0;
/*!re2c
        re2c:yyfill:enable = 0;
        re2c:label:prefix = "node";
        re2c:variable:yystate = "lexer_state";

        [a]+ { return 1; }
        [b]+ { return 2; }
        *    { return 0; }
    */
}

test "computed-continue custom state and DFA labels" {
    const Case = struct { input: [:0]const u8, expected: u8 };
    const cases = [_]Case{
        .{ .input = "aaa", .expected = 1 },
        .{ .input = "bbb", .expected = 2 },
        .{ .input = "123", .expected = 0 },
    };

    for (cases) |case| {
        try std.testing.expectEqual(case.expected, lex(case.input));
    }
}
