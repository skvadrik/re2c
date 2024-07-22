// re2zig $INPUT -o $OUTPUT

const std = @import("std");

/*!re2c
    re2c:api = custom;
    re2c:yyfill:enable = 0;
    re2c:define:YYPEEK      = "str[@intCast(cur)]";
    re2c:define:YYSKIP      = "cur += 1;";
    re2c:define:YYBACKUP    = "mar = cur;";
    re2c:define:YYRESTORE   = "cur = mar;";
    re2c:define:YYSTAGP     = "@@{tag} = cur;";
    re2c:define:YYSTAGN     = "@@{tag} = -1;";
    re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift};";
*/

fn lex_tags(str: [:0]const u8) isize {
    var cur: isize = 0;
    var mar: isize = 0;
    /*!stags:re2c:b1 format = 'var @@: isize = -1;\n'; */
    var x: isize = 0;
    var y: isize = 0;

    /*!re2c:b1
        re2c:tags = 1;
        ([b] @x [a] @y)? { return if (x == -1) -1 else y - x; }
    */
}

/*!maxnmatch:re2c*/

fn lex_captures(str: [:0]const u8) isize {
    var cur: isize = 0;
    /*!stags:re2c:b2 format = 'var @@: isize = -1;\n'; */
    var yypmatch: [yymaxnmatch * 2]isize = undefined;
    var yynmatch: usize = 0;

    /*!re2c:b2
        re2c:posix-captures = 1;
        (([a]))? {
            std.debug.assert(yynmatch == 3);
            return yypmatch[4];
        }
    */
}

test {
    try std.testing.expectEqual(lex_tags(""), -1);
    try std.testing.expectEqual(lex_tags("ba"), 1);
    try std.testing.expectEqual(lex_captures(""), -1);
    try std.testing.expectEqual(lex_captures("a"), 0);
}
