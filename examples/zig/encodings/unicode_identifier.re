// re2zig $INPUT -o $OUTPUT --utf8

const std = @import("std");

%{include "unicode_categories.re" %}

fn lex(yyinput: [:0]const u8) bool {
    var yycursor: u32 = 0;
    var yymarker: u32 = 0;

    %{
        re2c:yyfill:enable = 0;

        // Simplified "Unicode Identifier and Pattern Syntax"
        // (see https://unicode.org/reports/tr31)
        id_start    = L | Nl | [$_];
        id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
        identifier  = id_start id_continue*;

        identifier { return true; }
        *          { return false; }
    %}
}

test {
    try std.testing.expect(lex("_Ыдентификатор"));
}
