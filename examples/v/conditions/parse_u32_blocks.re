// re2v $INPUT -o $OUTPUT -i

const u32_lim = u64(1) << 32

fn parse_u32(yyinput string) ?u32 {
    mut yycursor, mut yymarker := 0, 0
    mut n := u64(0)
    mut yych := 0

    adddgt := fn (num u64, base u64, digit u8) u64 {
        n := num * base + u64(digit)
        return if n >= u32_lim { u32_lim } else { n }
    }
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:yych:emit = 0;

        end = "\x00";

        '0b' / [01]        { unsafe{ goto bin } }
        "0"                { unsafe{ goto oct } }
        ""   / [1-9]       { unsafe{ goto dec } }
        '0x' / [0-9a-fA-F] { unsafe{ goto hex } }
        *                  { return none }
    */
bin:
    /*!re2c
        end   { unsafe{ goto end } }
        [01]  { n = adddgt(n, 2, yyinput[yycursor-1] - 48); unsafe{ goto bin } }
        *     { return none }
    */
oct:
    /*!re2c
        end   { unsafe{ goto end } }
        [0-7] { n = adddgt(n, 8, yyinput[yycursor-1] - 48); unsafe{ goto oct } }
        *     { return none }
    */
dec:
    /*!re2c
        end   { unsafe{ goto end } }
        [0-9] { n = adddgt(n, 10, yyinput[yycursor-1] - 48); unsafe{ goto dec } }
        *     { return none }
    */
hex:
    /*!re2c
        end   { unsafe{ goto end } }
        [0-9] { n = adddgt(n, 16, yyinput[yycursor-1] - 48); unsafe{ goto hex } }
        [a-f] { n = adddgt(n, 16, yyinput[yycursor-1] - 87); unsafe{ goto hex } }
        [A-F] { n = adddgt(n, 16, yyinput[yycursor-1] - 55); unsafe{ goto hex } }
        *     { return none }
    */
end:
    if n < u32_lim {
        return u32(n)
    }
    return none
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
