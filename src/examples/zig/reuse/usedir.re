// re2zig $INPUT -o $OUTPUT

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

const std = @import("std");

const Ans = enum {color, fish, dunno};

%{rules:colors
    *                            { @panic("ah"); }
    "red" | "salmon" | "magenta" { return Ans.color; }
%}

%{rules:fish
    *                            { @panic("oh"); }
    "haddock" | "salmon" | "eel" { return Ans.fish; }
%}

fn lex(yyinput: [:0]const u8) Ans {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    %{
        re2c:yyfill:enable = 0;

        !use:fish;
        !use:colors;
        * { return Ans.dunno; } // overrides inherited '*' rules
    %}
}

test {
    try std.testing.expectEqual(lex("salmon"), Ans.fish);
    try std.testing.expectEqual(lex("what?"), Ans.dunno);
}
