<?php
// re2php $INPUT -o $OUTPUT -c

/*!conditions:re2c*/

function parse_u32($yyinput) {
    $yycursor = 0;
    $yycond = YYC_INIT;
    $n = 0;

    while (true) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:indent:top = 2;

        <INIT> '0b' / [01]        :=> BIN
        <INIT> "0"                :=> OCT
        <INIT> "" / [1-9]         :=> DEC
        <INIT> '0x' / [0-9a-fA-F] :=> HEX
        <INIT> * { return null; }

        <BIN> [01]  { $n = $n * 2 + (ord($yyinput[$yycursor - 1]) - 48); break 2; }
        <OCT> [0-7] { $n = $n * 8 + (ord($yyinput[$yycursor - 1]) - 48); break 2; }
        <DEC> [0-9] { $n = $n * 10 + (ord($yyinput[$yycursor - 1]) - 48); break 2; }
        <HEX> [0-9] { $n = $n * 16 + (ord($yyinput[$yycursor - 1]) - 48); break 2; }
        <HEX> [a-f] { $n = $n * 16 + (ord($yyinput[$yycursor - 1]) - 87); break 2; }
        <HEX> [A-F] { $n = $n * 16 + (ord($yyinput[$yycursor - 1]) - 55); break 2; }

        <BIN, OCT, DEC, HEX> * { return $n; }
    */
    }
}

function test($s, $n) {
    if (parse_u32($s) != $n) {
        throw new \Exception("error!");
    }
}

test("\0", null);
test("1234567890\0", 1234567890);
test("0b1101\0", 13);
test("0x7Fe\0", 2046);
test("0644\0", 420);
test("9999999999\0", 9999999999);
