// re2zig $INPUT -o $OUTPUT

const std = @import("std");

%{rules
    re2c:api = generic;
    re2c:YYSKIP = "cur += 1;";
    re2c:yyfill:enable = 0;

    [\xff] { return true; }
    *      { return false; }
%}

fn lex_unsigned(str: [:0]const u8) bool {
    var cur: u32 = 0;
    %{use
        re2c:YYCTYPE = "u8";
        re2c:YYPEEK = "str[cur]";
    %}
}

fn lex_signed(str: [:0]const u8) bool {
    var cur: u32 = 0;
    %{use
        re2c:YYCTYPE = "i8"; // should be unsigned!
        re2c:YYPEEK = "@bitCast(str[cur])";
    %}
}

test {
    try std.testing.expect(lex_unsigned("\xff"));
    try std.testing.expect(!lex_signed("\xff")); // error - lexer works incorrectly
}
