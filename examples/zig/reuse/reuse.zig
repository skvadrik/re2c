// Generated by re2zig
// re2zig $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.

const std = @import("std");



fn lex_utf8(yyinput: []const u8) ?usize {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    
    var yych: u8 = 0;
    var yystate: u32 = 0;
    yyl: while (true) {
        switch (yystate) {
            0 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                switch (yych) {
                    0xE2 => {
                        yystate = 3;
                        continue :yyl;
                    },
                    else => {
                        yystate = 1;
                        continue :yyl;
                    },
                }
            },
            1 => {
                yystate = 2;
                continue :yyl;
            },
            2 => { return null; },
            3 => {
                yymarker = yycursor;
                yych = yyinput[yycursor];
                switch (yych) {
                    0x88 => {
                        yycursor += 1;
                        yystate = 4;
                        continue :yyl;
                    },
                    else => {
                        yystate = 2;
                        continue :yyl;
                    },
                }
            },
            4 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x80 => {
                        yycursor += 1;
                        yystate = 6;
                        continue :yyl;
                    },
                    else => {
                        yystate = 5;
                        continue :yyl;
                    },
                }
            },
            5 => {
                yycursor = yymarker;
                yystate = 2;
                continue :yyl;
            },
            6 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x78 => {
                        yycursor += 1;
                        yystate = 7;
                        continue :yyl;
                    },
                    else => {
                        yystate = 5;
                        continue :yyl;
                    },
                }
            },
            7 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x20 => {
                        yycursor += 1;
                        yystate = 8;
                        continue :yyl;
                    },
                    else => {
                        yystate = 5;
                        continue :yyl;
                    },
                }
            },
            8 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0xE2 => {
                        yycursor += 1;
                        yystate = 9;
                        continue :yyl;
                    },
                    else => {
                        yystate = 5;
                        continue :yyl;
                    },
                }
            },
            9 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x88 => {
                        yycursor += 1;
                        yystate = 10;
                        continue :yyl;
                    },
                    else => {
                        yystate = 5;
                        continue :yyl;
                    },
                }
            },
            10 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x83 => {
                        yycursor += 1;
                        yystate = 11;
                        continue :yyl;
                    },
                    else => {
                        yystate = 5;
                        continue :yyl;
                    },
                }
            },
            11 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x79 => {
                        yycursor += 1;
                        yystate = 12;
                        continue :yyl;
                    },
                    else => {
                        yystate = 5;
                        continue :yyl;
                    },
                }
            },
            12 => { return yycursor; },
            else => { @panic("internal lexer error"); },
        }
    }

}

fn lex_utf32(yyinput: []const u32) ?usize {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    
    var yych: u32 = 0;
    var yystate: u32 = 0;
    yyl: while (true) {
        switch (yystate) {
            0 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                if (yych == 0x00002200) {
                    yystate = 2;
                    continue :yyl;
                }
                yystate = 1;
                continue :yyl;
            },
            1 => { return null; },
            2 => {
                yymarker = yycursor;
                yych = yyinput[yycursor];
                if (yych != 0x00000078) {
                    yystate = 1;
                    continue :yyl;
                }
                yycursor += 1;
                yych = yyinput[yycursor];
                if (yych == 0x00000020) {
                    yycursor += 1;
                    yystate = 4;
                    continue :yyl;
                }
                yystate = 3;
                continue :yyl;
            },
            3 => {
                yycursor = yymarker;
                yystate = 1;
                continue :yyl;
            },
            4 => {
                yych = yyinput[yycursor];
                if (yych != 0x00002203) {
                    yystate = 3;
                    continue :yyl;
                }
                yycursor += 1;
                yych = yyinput[yycursor];
                if (yych != 0x00000079) {
                    yystate = 3;
                    continue :yyl;
                }
                yycursor += 1;
                return yycursor;
            },
            else => { @panic("internal lexer error"); },
        }
    }

}

test {
    const s8 = [_]u8{0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79};
    try std.testing.expectEqual(lex_utf8(&s8), s8.len);

    const s32 = [_]u32{0x2200, 0x78, 0x20, 0x2203, 0x79};
    try std.testing.expectEqual(lex_utf32(&s32), s32.len);
}