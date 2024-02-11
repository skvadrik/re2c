// re2rust $INPUT -o $OUTPUT -c --recursive-functions
#![allow(non_snake_case)]

/*!conditions:re2c*/

const ERROR: u64 = std::u32::MAX as u64 + 1; // overflow

// Add digit with the given base, checking for overflow.
fn add(st: &mut State, offs: u8, base: u64) {
    let digit = unsafe { st.str.get_unchecked(st.cur - 1) } - offs;
    st.num = std::cmp::min(st.num * base + digit as u64, ERROR);
}

fn parse_u32(s: & [u8]) -> Option<u32> {
    let mut st = State {str: s, cur: 0, mar: 0, cond: YYC_INIT, num: 0};
    parse_start(&mut st)
}

// Store u32 number in u64 during parsing to simplify overflow hadling.
struct State<'a> {
    str: &'a [u8],
    cur: usize,
    mar: usize,
    cond: usize,
    num: u64,
}

/*!re2c
    re2c:define:YYFN      = ["parse_start;Option<u32>", "_st;&mut State"];
    re2c:define:YYCTYPE   = u8;
    re2c:define:YYPEEK    = "*_st.str.get_unchecked(_st.cur)";
    re2c:define:YYSKIP    = "_st.cur += 1;";
    re2c:define:YYBACKUP  = "_st.mar = _st.cur;";
    re2c:define:YYRESTORE = "_st.cur = _st.mar;";
    re2c:define:YYSHIFT   = "_st.cur = (_st.cur as isize + @@) as usize;";
    re2c:define:YYGETCONDITION = "_st.cond";
    re2c:define:YYSETCONDITION = "_st.cond = @@;";
    re2c:yyfill:enable = 0;

    <INIT> '0b' / [01]        :=> BIN
    <INIT> "0"                :=> OCT
    <INIT> "" / [1-9]         :=> DEC
    <INIT> '0x' / [0-9a-fA-F] :=> HEX
    <INIT> * { return None; }

    <BIN> [01]  { add(_st, 48, 2);  return yyfnBIN(_st); }
    <OCT> [0-7] { add(_st, 48, 8);  return yyfnOCT(_st); }
    <DEC> [0-9] { add(_st, 48, 10); return yyfnDEC(_st); }
    <HEX> [0-9] { add(_st, 48, 16); return yyfnHEX(_st); }
    <HEX> [a-f] { add(_st, 87, 16); return yyfnHEX(_st); }
    <HEX> [A-F] { add(_st, 55, 16); return yyfnHEX(_st); }

    <BIN, OCT, DEC, HEX> * {
        return if _st.num < ERROR { Some(_st.num as u32) } else { None };
    }
*/

fn main() {
    assert_eq!(parse_u32(b"\0"), None);
    assert_eq!(parse_u32(b"1234567890\0"), Some(1234567890));
    assert_eq!(parse_u32(b"0b1101\0"), Some(13));
    assert_eq!(parse_u32(b"0x7Fe\0"), Some(2046));
    assert_eq!(parse_u32(b"0644\0"), Some(420));
    assert_eq!(parse_u32(b"9999999999\0"), None);
}
