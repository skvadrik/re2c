// Generated by re2zig
// re2zig $INPUT -o $OUTPUT

const std = @import("std");

// Store u32 number in u64 during parsing to simplify overflow hadling.
const State = struct {
    yyinput: [:0]const u8,
    yycursor: usize,
    yymarker: usize,
    num: u64,
};

// Common re2c definitions shared between all functions.


const ERROR: u64 = @as(u64, std.math.maxInt(u32)) + 1; // overflow

// Add digit with the given base, checking for overflow.
fn add(st: *State, offs: u8, base: u64) void {
    const digit = st.yyinput[st.yycursor - 1] - offs;
    st.num = @min(st.num * base + digit, ERROR);
}

// Convert u64 to optional u32 (null meaning overflow or parse error).
fn maybeU32(num: u64) ?u32 {
    return if (num < ERROR) @intCast(num) else null;
}

fn parse_u32(s: [:0]const u8) ?u32 {
    var st = State {.yyinput = s, .yycursor = 0, .yymarker = 0, .num = 0};
    
    var yych: u8 = 0;
    var yystate: u32 = 0;
    while (true) {
        switch (yystate) {
            0 => {
                yych = st.yyinput[st.yycursor];
                st.yycursor += 1;
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
                st.yymarker = st.yycursor;
                yych = st.yyinput[st.yycursor];
                switch (yych) {
                    0x42,
                    0x62 => {
                        st.yycursor += 1;
                        yystate = 5;
                        continue;
                    },
                    0x58,
                    0x78 => {
                        st.yycursor += 1;
                        yystate = 7;
                        continue;
                    },
                    else => {
                        yystate = 3;
                        continue;
                    },
                }
            },
            3 => { return parse_oct(&st); },
            4 => {
                st.yycursor -= 1;
                return parse_dec(&st);
            },
            5 => {
                yych = st.yyinput[st.yycursor];
                switch (yych) {
                    0x30...0x31 => {
                        st.yycursor += 1;
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
                st.yycursor = st.yymarker;
                yystate = 3;
                continue;
            },
            7 => {
                yych = st.yyinput[st.yycursor];
                switch (yych) {
                    0x30...0x39,
                    0x41...0x46,
                    0x61...0x66 => {
                        st.yycursor += 1;
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
                st.yycursor -= 1;
                return parse_bin(&st);
            },
            9 => {
                st.yycursor -= 1;
                return parse_hex(&st);
            },
            else => { @panic("internal lexer error"); },
        }
    }

}

fn parse_bin(st: *State) ?u32 {
    bin: while (true) {
    var yych: u8 = 0;
    var yystate: u32 = 0;
    while (true) {
        switch (yystate) {
            0 => {
                yych = st.yyinput[st.yycursor];
                st.yycursor += 1;
                switch (yych) {
                    0x30...0x31 => {
                        yystate = 2;
                        continue;
                    },
                    else => {
                        yystate = 1;
                        continue;
                    },
                }
            },
            1 => { return maybeU32(st.num); },
            2 => { add(st, 48, 2); continue :bin; },
            else => { @panic("internal lexer error"); },
        }
    }
}
}

fn parse_oct(st: *State) ?u32 {
    oct: while (true) {
    var yych: u8 = 0;
    var yystate: u32 = 0;
    while (true) {
        switch (yystate) {
            0 => {
                yych = st.yyinput[st.yycursor];
                st.yycursor += 1;
                switch (yych) {
                    0x30...0x37 => {
                        yystate = 2;
                        continue;
                    },
                    else => {
                        yystate = 1;
                        continue;
                    },
                }
            },
            1 => { return maybeU32(st.num); },
            2 => { add(st, 48, 8); continue :oct; },
            else => { @panic("internal lexer error"); },
        }
    }
}
}

fn parse_dec(st: *State) ?u32 {
    dec: while (true) {
    var yych: u8 = 0;
    var yystate: u32 = 0;
    while (true) {
        switch (yystate) {
            0 => {
                yych = st.yyinput[st.yycursor];
                st.yycursor += 1;
                switch (yych) {
                    0x30...0x39 => {
                        yystate = 2;
                        continue;
                    },
                    else => {
                        yystate = 1;
                        continue;
                    },
                }
            },
            1 => { return maybeU32(st.num); },
            2 => { add(st, 48, 10); continue :dec; },
            else => { @panic("internal lexer error"); },
        }
    }
}
}

fn parse_hex(st: *State) ?u32 {
    hex: while (true) {
    var yych: u8 = 0;
    var yystate: u32 = 0;
    while (true) {
        switch (yystate) {
            0 => {
                yych = st.yyinput[st.yycursor];
                st.yycursor += 1;
                switch (yych) {
                    0x30...0x39 => {
                        yystate = 2;
                        continue;
                    },
                    0x41...0x46 => {
                        yystate = 3;
                        continue;
                    },
                    0x61...0x66 => {
                        yystate = 4;
                        continue;
                    },
                    else => {
                        yystate = 1;
                        continue;
                    },
                }
            },
            1 => { return maybeU32(st.num); },
            2 => { add(st, 48, 16); continue :hex; },
            3 => { add(st, 55, 16); continue :hex; },
            4 => { add(st, 87, 16); continue :hex; },
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
