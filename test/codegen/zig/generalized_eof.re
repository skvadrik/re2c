// re2zig $INPUT -o $OUTPUT

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

fn run(str: [:0]const u8, ret: i32) !void {
    try std.testing.expectEqual(lex_simple(str), ret);
    try std.testing.expectEqual(lex_eof(str), ret);
    try std.testing.expectEqual(try lex_scc(str), ret);
}

test {
    try run("", 0);
    try run("a", 2);
    try run("ax", 3);
    try run("b", 4);
    try run("bx", 4);
    try run("ccc", 5);
}
