// re2js $INPUT -o $OUTPUT -c

/*!conditions:re2c*/

function parse_u32(yyinput) {
    let yycursor = 0
    let yycond = YYC_INIT
    let n = 0

    loop: while (true) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:indent:top = 2;

        <INIT> '0b' / [01]        :=> BIN
        <INIT> "0"                :=> OCT
        <INIT> "" / [1-9]         :=> DEC
        <INIT> '0x' / [0-9a-fA-F] :=> HEX
        <INIT> * { return null }

        <BIN> [01]  { n = n * 2 + (yyinput.charCodeAt(yycursor - 1) - 48); continue loop }
        <OCT> [0-7] { n = n * 8 + (yyinput.charCodeAt(yycursor - 1) - 48); continue loop }
        <DEC> [0-9] { n = n * 10 + (yyinput.charCodeAt(yycursor - 1) - 48); continue loop }
        <HEX> [0-9] { n = n * 16 + (yyinput.charCodeAt(yycursor - 1) - 48); continue loop }
        <HEX> [a-f] { n = n * 16 + (yyinput.charCodeAt(yycursor - 1) - 87); continue loop }
        <HEX> [A-F] { n = n * 16 + (yyinput.charCodeAt(yycursor - 1) - 55); continue loop }

        <BIN, OCT, DEC, HEX> * { return n }
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
