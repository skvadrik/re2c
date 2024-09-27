// re2v $INPUT -o $OUTPUT -ci

/*!conditions:re2c*/

const u32_lim = u64(1) << 32

fn parse_u32(yyinput string) ?u32 {
    mut yycursor, mut yymarker := 0, 0
    mut n := u64(0)
    mut yycond := YYCONDTYPE.yycinit

    adddgt := fn (num u64, base u64, digit u8) u64 {
        n := num * base + u64(digit)
        return if n >= u32_lim { u32_lim } else { n }
    }

    /*!re2c
        re2c:yyfill:enable = 0;

        <*> * { return none }

        <init> '0b' / [01]        :=> bin
        <init> "0"                :=> oct
        <init> ""   / [1-9]       :=> dec
        <init> '0x' / [0-9a-fA-F] :=> hex

        <bin, oct, dec, hex> "\x00" { return if n < u32_lim { u32(n) } else { none } }

        <bin> [01]  { n = adddgt(n, 2,  yyinput[yycursor-1] - 48); unsafe{ goto yyc_bin } }
        <oct> [0-7] { n = adddgt(n, 8,  yyinput[yycursor-1] - 48); unsafe{ goto yyc_oct } }
        <dec> [0-9] { n = adddgt(n, 10, yyinput[yycursor-1] - 48); unsafe{ goto yyc_dec } }
        <hex> [0-9] { n = adddgt(n, 16, yyinput[yycursor-1] - 48); unsafe{ goto yyc_hex } }
        <hex> [a-f] { n = adddgt(n, 16, yyinput[yycursor-1] - 87); unsafe{ goto yyc_hex } }
        <hex> [A-F] { n = adddgt(n, 16, yyinput[yycursor-1] - 55); unsafe{ goto yyc_hex } }
    */
}

fn main() {
    test := fn (num ?u32, str string) {
        if n := parse_u32(str) {
            if m := num { if n != m { panic("wrong number") } }
        } else {
            if _ := num { panic("expected none") }
        }
    }
    test(1234567890, "1234567890\0")
    test(13, "0b1101\0")
    test(0x7fe, "0x007Fe\0")
    test(0o644, "0644\0")
    test(none, "9999999999\0")
    test(none, "123??\0")
}
