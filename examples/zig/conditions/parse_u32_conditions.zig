// Generated by re2zig
// re2zig $INPUT -o $OUTPUT -c

const std = @import("std");

const yycinit: u32 = 0;
const yycbin: u32 = 10;
const yycoct: u32 = 13;
const yycdec: u32 = 16;
const yychex: u32 = 19;


const ERROR: u64 = @as(u64, std.math.maxInt(u32)) + 1; // overflow

// Add digit with the given base, checking for overflow.
fn add(num: *u64, str: [:0]const u8, cur: usize, offs: u8, base: u64) void {
    num.* = @min(num.* * base + (str[cur - 1] - offs), ERROR);
}

fn parse_u32(yyinput: [:0]const u8) ?u32 {
    var yycursor: usize = 0;
    var yymarker: usize = 0;
    var yycond = yycinit;
    var num: u64 = 0; // Store number in u64 to simplify overflow checks.

    loop: while(true) {
    
    var yych: u8 = 0;
    var yystate: u32 = yycond;
    while (true) {
        switch (yystate) {
            0 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                switch (yych) {
                    0x30 => {
                        yystate = 2;
                        continue;
                    },
                    0x31...0x39 => {
                        yystate = 4;
                        continue;
                    },
                    else => {
                        yystate = 1;
                        continue;
                    },
                }
            },
            1 => { return null; },
            2 => {
                yymarker = yycursor;
                yych = yyinput[yycursor];
                switch (yych) {
                    0x42,
                    0x62 => {
                        yycursor += 1;
                        yystate = 5;
                        continue;
                    },
                    0x58,
                    0x78 => {
                        yycursor += 1;
                        yystate = 7;
                        continue;
                    },
                    else => {
                        yystate = 3;
                        continue;
                    },
                }
            },
            3 => {
                yycond = yycoct;
                yystate = yycoct;
                continue;
            },
            4 => {
                yycursor -= 1;
                yycond = yycdec;
                yystate = yycdec;
                continue;
            },
            5 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x30...0x31 => {
                        yycursor += 1;
                        yystate = 8;
                        continue;
                    },
                    else => {
                        yystate = 6;
                        continue;
                    },
                }
            },
            6 => {
                yycursor = yymarker;
                yystate = 3;
                continue;
            },
            7 => {
                yych = yyinput[yycursor];
                switch (yych) {
                    0x30...0x39,
                    0x41...0x46,
                    0x61...0x66 => {
                        yycursor += 1;
                        yystate = 9;
                        continue;
                    },
                    else => {
                        yystate = 6;
                        continue;
                    },
                }
            },
            8 => {
                yycursor -= 1;
                yycond = yycbin;
                yystate = yycbin;
                continue;
            },
            9 => {
                yycursor -= 1;
                yycond = yychex;
                yystate = yychex;
                continue;
            },
            10 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                switch (yych) {
                    0x30...0x31 => {
                        yystate = 12;
                        continue;
                    },
                    else => {
                        yystate = 11;
                        continue;
                    },
                }
            },
            11 => { 
            return if (num < ERROR) @intCast(num) else null;
 },
            12 => { add(&num, yyinput, yycursor, 48, 2);  continue :loop; },
            13 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                switch (yych) {
                    0x30...0x37 => {
                        yystate = 15;
                        continue;
                    },
                    else => {
                        yystate = 14;
                        continue;
                    },
                }
            },
            14 => { 
            return if (num < ERROR) @intCast(num) else null;
 },
            15 => { add(&num, yyinput, yycursor, 48, 8);  continue :loop; },
            16 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                switch (yych) {
                    0x30...0x39 => {
                        yystate = 18;
                        continue;
                    },
                    else => {
                        yystate = 17;
                        continue;
                    },
                }
            },
            17 => { 
            return if (num < ERROR) @intCast(num) else null;
 },
            18 => { add(&num, yyinput, yycursor, 48, 10); continue :loop; },
            19 => {
                yych = yyinput[yycursor];
                yycursor += 1;
                switch (yych) {
                    0x30...0x39 => {
                        yystate = 21;
                        continue;
                    },
                    0x41...0x46 => {
                        yystate = 22;
                        continue;
                    },
                    0x61...0x66 => {
                        yystate = 23;
                        continue;
                    },
                    else => {
                        yystate = 20;
                        continue;
                    },
                }
            },
            20 => { 
            return if (num < ERROR) @intCast(num) else null;
 },
            21 => { add(&num, yyinput, yycursor, 48, 16); continue :loop; },
            22 => { add(&num, yyinput, yycursor, 55, 16); continue :loop; },
            23 => { add(&num, yyinput, yycursor, 87, 16); continue :loop; },
            else => { @panic("internal lexer error"); },
        }
    }
}
}

test {
    try std.testing.expectEqual(parse_u32(""), null);
    try std.testing.expectEqual(parse_u32("1234567890"), 1234567890);
    try std.testing.expectEqual(parse_u32("0b1101"), 13);
    try std.testing.expectEqual(parse_u32("0x7Fe"), 2046);
    try std.testing.expectEqual(parse_u32("0644"), 420);
    try std.testing.expectEqual(parse_u32("9999999999"), null);
}
