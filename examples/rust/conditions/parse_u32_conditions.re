// re2rust $INPUT -o $OUTPUT -c

/*!types:re2c*/

const ERROR: u64 = std::u32::MAX as u64 + 1;

fn add(num: u64, dgt: u8, base: u64) -> u64 {
    return std::cmp::min(num * base + dgt as u64, ERROR)
}

fn parse_u32(s: &[u8]) -> Option<u32> {
    let mut cur = 0;
    let mut mar = 0;
    let mut cond = YYC_INIT;
    let mut num = 0u64;

    'lex : loop {/*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = u8;
        re2c:define:YYPEEK = "*s.get_unchecked(cur)";
        re2c:define:YYSKIP = "cur += 1;";
        re2c:define:YYBACKUP = "mar = cur;";
        re2c:define:YYRESTORE = "cur = mar;";
        re2c:define:YYSHIFT = "cur = (cur as isize + @@) as usize;";
        re2c:define:YYGETCONDITION = "cond";
        re2c:define:YYSETCONDITION = "cond = @@;";

        <*> * { return None; }

        <INIT> '0b' / [01]        :=> BIN
        <INIT> "0"                :=> OCT
        <INIT> "" / [1-9]         :=> DEC
        <INIT> '0x' / [0-9a-fA-F] :=> HEX

        <BIN, OCT, DEC, HEX> "\x00" {
            return if num < ERROR { Some(num as u32) } else { None };
        }

        <BIN> [01]  { num = add(num, s[cur-1] - 48, 2);  continue 'lex; }
        <OCT> [0-7] { num = add(num, s[cur-1] - 48, 8);  continue 'lex; }
        <DEC> [0-9] { num = add(num, s[cur-1] - 48, 10); continue 'lex; }
        <HEX> [0-9] { num = add(num, s[cur-1] - 48, 16); continue 'lex; }
        <HEX> [a-f] { num = add(num, s[cur-1] - 87, 16); continue 'lex; }
        <HEX> [A-F] { num = add(num, s[cur-1] - 55, 16); continue 'lex; }
    */}
}

fn main() {
    assert_eq!(parse_u32(b"1234567890\0"), Some(1234567890));
    assert_eq!(parse_u32(b"0b1101\0"), Some(13));
    assert_eq!(parse_u32(b"0x7Fe\0"), Some(2046));
    assert_eq!(parse_u32(b"0644\0"), Some(420));
    assert_eq!(parse_u32(b"9999999999\0"), None);
    assert_eq!(parse_u32(b"\0"), None);
}
