<?php
// re2php $INPUT -o $OUTPUT

/*!re2c // Common re2c definitions shared between all functions.
    re2c:api = record;
    re2c:yyrecord = $st;
    re2c:yyfill:enable = 0;
*/

function parse_u32($str) {
    $st = new \stdClass();
    $st->yyinput = $str;
    $st->yycursor = 0;
    $st->yymarker = 0;

    /*!re2c
        '0b' / [01]        { return parse_bin($st); }
        "0"                { return parse_oct($st); }
        "" / [1-9]         { return parse_dec($st); }
        '0x' / [0-9a-fA-F] { return parse_hex($st); }
        *                  { return null; }
    */
}

function parse_bin($st): int {
    $n = 0;
    while (true) {
    /*!re2c
        [01] { $n = $n * 2 + (ord($st->yyinput[$st->yycursor - 1]) - 48); break 2; }
        *    { return $n; }
    */
    }
}

function parse_oct($st): int {
    $n = 0;
    while (true) {
    /*!re2c
        [0-7] { $n = $n * 8 + (ord($st->yyinput[$st->yycursor - 1]) - 48); break 2; }
        *     { return $n; }
    */
    }
}

function parse_dec($st): int {
    $n = 0;
    while (true) {
    /*!re2c
        [0-9] {
            $n = $n * 10 + (ord($st->yyinput[$st->yycursor - 1]) - 48);
            break 2;
        }
        * { return $n; }
    */
    }
}

function parse_hex($st): int {
    $n = 0;
    while (true) {
    /*!re2c
        [0-9] { $n = $n * 16 + (ord($st->yyinput[$st->yycursor - 1]) - 48); break 2; }
        [a-f] { $n = $n * 16 + (ord($st->yyinput[$st->yycursor - 1]) - 87); break 2; }
        [A-F] { $n = $n * 16 + (ord($st->yyinput[$st->yycursor - 1]) - 55); break 2; }
        *     { return $n; }
    */
    }
}

function test($s, $n): void {
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
