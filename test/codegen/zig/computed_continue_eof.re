// re2zig $INPUT -o $OUTPUT --loop-switch --computed-continue --no-generation-date --no-version

const std = @import("std");

%{rules:x
    $           { return 0; }
    *           { return 1; }
    [a] $       { return 2; }
    [a]         { return 3; }
    [b] $ | [b] { return 4; }
    [c]+ $      { return 5; }
%}

fn lex_simple(yyinput: [:0]const u8) i32 {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    const yylimit: usize = yyinput.len;

    %{use:x
        re2c:yyfill:enable = 0;
    %}
}

fn lex_eof(yyinput: [:0]const u8) i32 {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    const yylimit: usize = yyinput.len;

    %{use:x
        re2c:eof = 0;
        re2c:YYFILL = "false";
        re2c:YYEND = "yycursor == yylimit";
    %}
}

%{max %}

fn lex_scc(str: [:0]const u8) !i32 {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    const end: usize = str.len;
    const yylimit: usize = end + yymaxfill;

    var yyinput = try std.testing.allocator.alloc(u8, yylimit);
    defer std.testing.allocator.free(yyinput);
    std.mem.copyForwards(u8, yyinput[0..], str);
    std.mem.copyForwards(u8, yyinput[end..], &[_]u8{0} ** yymaxfill);

    %{use:x
        re2c:YYFILL = "return -1;";
        re2c:YYEND = "yycursor == end";
    %}
}

test "computed-continue fill and EOF transitions" {
    const Case = struct { input: [:0]const u8, expected: i32 };
    const cases = [_]Case{
        .{ .input = "", .expected = 0 },
        .{ .input = "a", .expected = 2 },
        .{ .input = "ax", .expected = 3 },
        .{ .input = "b", .expected = 4 },
        .{ .input = "bx", .expected = 4 },
        .{ .input = "ccc", .expected = 5 },
    };

    for (cases) |case| {
        try std.testing.expectEqual(case.expected, lex_simple(case.input));
        try std.testing.expectEqual(case.expected, lex_eof(case.input));
        try std.testing.expectEqual(case.expected, try lex_scc(case.input));
    }
}
