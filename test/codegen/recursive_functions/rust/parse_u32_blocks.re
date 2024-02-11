// re2rust $INPUT -o $OUTPUT --recursive-functions
#![allow(unused_braces)]

const ERROR: u64 = std::u32::MAX as u64 + 1; // overflow

macro_rules! maybe { // Convert the number from u64 to optional u32.
    ($n:expr) => { if $n < ERROR { Some($n as u32) } else { None } }
}

// Add digit with the given base, checking for overflow.
fn add(st: &mut State, offs: u8, base: u64) {
    let digit = unsafe { st.str.get_unchecked(st.cur - 1) } - offs;
    st.num = std::cmp::min(st.num * base + digit as u64, ERROR);
}

fn parse_u32(s: & [u8]) -> Option<u32> {
    let mut st = State {str: s, cur: 0, mar: 0, num: 0};
    parse_start(&mut st)
}

// Store u32 number in u64 during parsing to simplify overflow hadling.
struct State<'a> {
    str: &'a [u8],
    cur: usize,
    mar: usize,
    num: u64,
}

/*!re2c // Common re2c definitions shared between all functions.
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE   = u8;
    re2c:define:YYPEEK    = "*_st.str.get_unchecked(_st.cur)";
    re2c:define:YYSKIP    = "_st.cur += 1;";
    re2c:define:YYBACKUP  = "_st.mar = _st.cur;";
    re2c:define:YYRESTORE = "_st.cur = _st.mar;";
    re2c:define:YYSHIFT   = "_st.cur = (_st.cur as isize + @@) as usize;";
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_start;Option<u32>", "_st;&mut State"];

    '0b' / [01]        { parse_bin(_st) }
    "0"                { parse_oct(_st) }
    "" / [1-9]         { parse_dec(_st) }
    '0x' / [0-9a-fA-F] { parse_hex(_st) }
    *                  { None }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_bin;Option<u32>", "_st;&mut State"];

    [01] { add(_st, 48, 2); parse_bin(_st) }
    *    { return maybe!(_st.num); }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_oct;Option<u32>", "_st;&mut State"];

    [0-7] { add(_st, 48, 8); parse_oct(_st) }
    *     { return maybe!(_st.num); }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_dec;Option<u32>", "_st;&mut State"];

    [0-9] { add(_st, 48, 10); parse_dec(_st) }
    *     { return maybe!(_st.num); }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_hex;Option<u32>", "_st;&mut State"];

    [0-9] { add(_st, 48, 16); parse_hex(_st) }
    [a-f] { add(_st, 87, 16); parse_hex(_st) }
    [A-F] { add(_st, 55, 16); parse_hex(_st) }
    *     { return maybe!(_st.num); }
*/

fn main() {
    assert_eq!(parse_u32(b"\0"), None);
    assert_eq!(parse_u32(b"1234567890\0"), Some(1234567890));
    assert_eq!(parse_u32(b"0b1101\0"), Some(13));
    assert_eq!(parse_u32(b"0x7Fe\0"), Some(2046));
    assert_eq!(parse_u32(b"0644\0"), Some(420));
    assert_eq!(parse_u32(b"9999999999\0"), None);
}
