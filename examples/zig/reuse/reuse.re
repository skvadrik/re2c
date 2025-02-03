// re2zig $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.

const std = @import("std");

%{rules
    re2c:yyfill:enable = 0;

    "∀x ∃y" { return yycursor; }
    *       { return null; }
%}

fn lex_utf8(yyinput: []const u8) ?usize {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    %{use
        re2c:encoding:utf8 = 1;
        re2c:YYCTYPE = u8; // the default
    %}
}

fn lex_utf32(yyinput: []const u32) ?usize {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    %{use
        re2c:encoding:utf32 = 1;
        re2c:YYCTYPE = u32;
    %}
}

test {
    const s8 = [_]u8{0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79};
    try std.testing.expectEqual(lex_utf8(&s8), s8.len);

    const s32 = [_]u32{0x2200, 0x78, 0x20, 0x2203, 0x79};
    try std.testing.expectEqual(lex_utf32(&s32), s32.len);
}
