// re2js $INPUT -o $OUTPUT

/*!re2c // Common re2c definitions shared between all functions.
    re2c:api = record;
    re2c:yyrecord = st;
    re2c:yyfill:enable = 0;
*/

function parse_u32(str) {
    let st = {
        yyinput: str,
        yycursor: 0,
        yymarker: 0
    }
    /*!re2c
        '0b' / [01]        { return parse_bin(st) }
        "0"                { return parse_oct(st) }
        "" / [1-9]         { return parse_dec(st) }
        '0x' / [0-9a-fA-F] { return parse_hex(st) }
        *                  { return null }
    */
}

function parse_bin(st) {
    n = 0
    loop: while (true) {
    /*!re2c
        [01] { n = n * 2 + (st.yyinput.charCodeAt(st.yycursor - 1) - 48); continue loop }
        *    { return n }
    */
    }
}

function parse_oct(st) {
    n = 0
    loop: while (true) {
    /*!re2c
        [0-7] { n = n * 8 + (st.yyinput.charCodeAt(st.yycursor - 1) - 48); continue loop }
        *     { return n }
    */
    }
}

function parse_dec(st) {
    n = 0
    loop: while (true) {
    /*!re2c
        [0-9] { n = n * 10 + (st.yyinput.charCodeAt(st.yycursor - 1) - 48); continue loop }
        *     { return n }
    */
    }
}

function parse_hex(st) {
    n = 0
    loop: while (true) {
    /*!re2c
        [0-9] { n = n * 16 + (st.yyinput.charCodeAt(st.yycursor - 1) - 48); continue loop }
        [a-f] { n = n * 16 + (st.yyinput.charCodeAt(st.yycursor - 1) - 87); continue loop }
        [A-F] { n = n * 16 + (st.yyinput.charCodeAt(st.yycursor - 1) - 55); continue loop }
        *     { return n }
    */
    }
}

function test(s, n) {
    if (parse_u32(s) != n) throw "error!"
}

test("\0", null)
test("1234567890\0", 1234567890)
test("0b1101\0", 13)
test("0x7Fe\0", 2046)
test("0644\0", 420)
test("9999999999\0", 9999999999)
