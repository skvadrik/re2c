// re2zig $INPUT -o $OUTPUT --loop-switch --computed-continue --no-generation-date --no-version

const std = @import("std");

const Token = enum {
    identifier,
    invalid,
};

fn lex(yyinput: [:0]const u8) Token {
    var yycursor: u32 = 0;
/*!re2c
        re2c:yyfill:enable = 0;

        ident = [a-z]+;

        ident { return .identifier; }
        *     { return .invalid; }
    */
}

test {
    try std.testing.expectEqual(Token.identifier, lex("abc"));
    try std.testing.expectEqual(Token.invalid, lex("123"));
}
