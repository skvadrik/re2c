// Generated by re2zig
// re2zig $INPUT -o $OUTPUT -b

const std = @import("std");

fn lex(yyinput: [:0]const u8) bool {
    var yycursor: u32 = 0;
    
    var yych: u8 = 0;
    var yystate: u32 = 0;
    const yybm = [256]u8{
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
        128, 128, 128, 128, 128, 128, 128, 128,
        128, 128,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
    };
    yyl: while (true) {
        switch (yystate) {
            0 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                if (yych <= 0x30) {
                    yystate = 1;
                    continue :yyl;
                }
                if (yych <= 0x39) {
                    yystate = 2;
                    continue :yyl;
                }
                yystate = 1;
                continue :yyl;
            },
            1 => { return false; },
            2 => {
                yych = yyinput[yycursor];
                if ((yybm[0+yych] & 128) != 0) {
                    yycursor += 1;
                    yystate = 2;
                    continue :yyl;
                }
                return true;
            },
            else => { @panic("internal lexer error"); },
        }
    }

}

test {
    try std.testing.expect(lex("1234"));
}
