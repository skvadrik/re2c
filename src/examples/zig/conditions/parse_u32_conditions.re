// re2zig $INPUT -o $OUTPUT -c

const std = @import("std");

%{conditions %}

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
    %{
        re2c:yyfill:enable = 0;

        <init> '0b' / [01]        :=> bin
        <init> "0"                :=> oct
        <init> "" / [1-9]         :=> dec
        <init> '0x' / [0-9a-fA-F] :=> hex
        <init> * { return null; }

        <bin> [01]  { add(&num, yyinput, yycursor, 48, 2);  continue :loop; }
        <oct> [0-7] { add(&num, yyinput, yycursor, 48, 8);  continue :loop; }
        <dec> [0-9] { add(&num, yyinput, yycursor, 48, 10); continue :loop; }
        <hex> [0-9] { add(&num, yyinput, yycursor, 48, 16); continue :loop; }
        <hex> [a-f] { add(&num, yyinput, yycursor, 87, 16); continue :loop; }
        <hex> [A-F] { add(&num, yyinput, yycursor, 55, 16); continue :loop; }

        <bin, oct, dec, hex> * {
            return if (num < ERROR) @intCast(num) else null;
        }
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
