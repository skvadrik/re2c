// re2zig $INPUT -o $OUTPUT

const std = @import("std");

// Store u32 number in u64 during parsing to simplify overflow handling.
const State = struct {
    yyinput: [:0]const u8,
    yycursor: usize,
    yymarker: usize,
    num: u64,
};

// Common re2c definitions shared between all functions.
%{
    re2c:api = record;
    re2c:yyrecord = st;
    re2c:yyfill:enable = 0;
%}

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
    %{
        '0b' / [01]        { return parse_bin(&st); }
        "0"                { return parse_oct(&st); }
        "" / [1-9]         { return parse_dec(&st); }
        '0x' / [0-9a-fA-F] { return parse_hex(&st); }
        *                  { return null; }
    %}
}

fn parse_bin(st: *State) ?u32 {
    bin: while (true) {%{
        [01] { add(st, 48, 2); continue :bin; }
        *    { return maybeU32(st.num); }
    %}}
}

fn parse_oct(st: *State) ?u32 {
    oct: while (true) {%{
        [0-7] { add(st, 48, 8); continue :oct; }
        *     { return maybeU32(st.num); }
    %}}
}

fn parse_dec(st: *State) ?u32 {
    dec: while (true) {%{
        [0-9] { add(st, 48, 10); continue :dec; }
        *     { return maybeU32(st.num); }
    %}}
}

fn parse_hex(st: *State) ?u32 {
    hex: while (true) {%{
        [0-9] { add(st, 48, 16); continue :hex; }
        [a-f] { add(st, 87, 16); continue :hex; }
        [A-F] { add(st, 55, 16); continue :hex; }
        *     { return maybeU32(st.num); }
    %}}
}

test {
    try std.testing.expectEqual(parse_u32(""), null);
    try std.testing.expectEqual(parse_u32("1234567890"), 1234567890);
    try std.testing.expectEqual(parse_u32("0b1101"), 13);
    try std.testing.expectEqual(parse_u32("0x7Fe"), 2046);
    try std.testing.expectEqual(parse_u32("0644"), 420);
    try std.testing.expectEqual(parse_u32("9999999999"), null);
}
