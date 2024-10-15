// re2zig $INPUT -o $OUTPUT

const std = @import("std");

%{include "definitions.zig" %}

fn lex(yyinput: [:0]const u8) Num {
    var yycursor: u32 = 0;
    var yymarker: u32 = 0;
    %{
        re2c:yyfill:enable = 0;

        *      { return Num.nan; }
        number { return Num.integer; }
        !include "extra_rules.re.inc";
    %}
}

test {
    try std.testing.expectEqual(lex("123"), Num.integer);
    try std.testing.expectEqual(lex("123.4567"), Num.floating);
}
