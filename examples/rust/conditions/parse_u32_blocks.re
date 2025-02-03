// re2rust $INPUT -o $OUTPUT

// Store u32 number in u64 during parsing to simplify overflow handling.
struct State<'a> {
    yyinput: &'a [u8],
    yycursor: usize,
    yymarker: usize,
    num: u64,
}

/*!re2c // Common re2c definitions shared between all functions.
    re2c:api = record;
    re2c:yyrecord = st;
    re2c:yyfill:enable = 0;
    re2c:YYCTYPE = u8;
*/

const ERROR: u64 = std::u32::MAX as u64 + 1; // overflow

macro_rules! maybe { // Convert the number from u64 to optional u32.
    ($n:expr) => { if $n < ERROR { Some($n as u32) } else { None } }
}

// Add digit with the given base, checking for overflow.
fn add(st: &mut State, offs: u8, base: u64) {
    let digit = unsafe { st.yyinput.get_unchecked(st.yycursor - 1) } - offs;
    st.num = std::cmp::min(st.num * base + digit as u64, ERROR);
}

fn parse_u32(s: & [u8]) -> Option<u32> {
    assert_eq!(s.last(), Some(&0)); // expect null-terminated input

    let mut st = State {yyinput: s, yycursor: 0, yymarker: 0, num: 0};
/*!re2c
    '0b' / [01]        { return parse_bin(&mut st); }
    "0"                { return parse_oct(&mut st); }
    "" / [1-9]         { return parse_dec(&mut st); }
    '0x' / [0-9a-fA-F] { return parse_hex(&mut st); }
    *                  { return None; }
*/
}

fn parse_bin(st: &mut State) -> Option<u32> {
    'bin: loop {/*!re2c
        [01] { add(st, 48, 2); continue 'bin; }
        *    { return maybe!(st.num); }
    */}
}

fn parse_oct(st: &mut State) -> Option<u32> {
    'oct: loop {/*!re2c
        [0-7] { add(st, 48, 8); continue 'oct; }
        *     { return maybe!(st.num); }
    */}
}

fn parse_dec(st: &mut State) -> Option<u32> {
    'dec: loop {/*!re2c
        [0-9] { add(st, 48, 10); continue 'dec; }
        *     { return maybe!(st.num); }
    */}
}

fn parse_hex(st: &mut State) -> Option<u32> {
    'hex: loop {/*!re2c
        [0-9] { add(st, 48, 16); continue 'hex; }
        [a-f] { add(st, 87, 16); continue 'hex; }
        [A-F] { add(st, 55, 16); continue 'hex; }
        *     { return maybe!(st.num); }
    */}
}

fn main() {
    assert_eq!(parse_u32(b"\0"), None);
    assert_eq!(parse_u32(b"1234567890\0"), Some(1234567890));
    assert_eq!(parse_u32(b"0b1101\0"), Some(13));
    assert_eq!(parse_u32(b"0x7Fe\0"), Some(2046));
    assert_eq!(parse_u32(b"0644\0"), Some(420));
    assert_eq!(parse_u32(b"9999999999\0"), None);
}
