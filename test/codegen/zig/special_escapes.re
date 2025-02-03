// re2zig $INPUT -o $OUTPUT

const std = @import("std");

fn lex(yyinput: [:0]const u8) bool {
    var yycursor: u32 = 0;
    var yymarker: u32 = 0;
    %{
        re2c:yyfill:enable = 0;

        "\a\b\f\n\r\t\v\\'\"" { return true; }
        * { return false; }
    %}
}

test {
    try std.testing.expect(lex("\x07\x08\x0c\x0a\x0d\x09\x0b\\'\""));
}
