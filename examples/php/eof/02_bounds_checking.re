<?php
// re2php $INPUT -o $OUTPUT

/*!max:re2c*/

function lex($yyinput) {
    $yycursor = 0;
    $yylimit = strlen($yyinput);
    $count = 0;

    while (true) {
    /*!re2c
        re2c:YYFILL = "return -1";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // check that it is the sentinel, not some unexpected null
            return ($yycursor == $yylimit - YYMAXFILL + 1) ? $count : -1;
        }
        str  { $count += 1; break 2; }
        [ ]+ { break 2; }
        *    { return -1; }
    */
    }
}

function test($s, $n) {
    $padded_s = $s . str_repeat("\0", YYMAXFILL);
    if (lex($padded_s) != $n) {
        throw new \Exception("error!");
    }
}

test("", 0);
test("'unterminated\\'", -1);
test("'qu\0tes' 'are' 'fine: \\'' ", 3);
test("'unexpected \0 null", -1);
