<?php
// re2php $INPUT -o $OUTPUT

// expects a string without terminating null
function lex($str) {
    $cur = 0;
    $lim = strlen($str);
    $count = 0;

    while (true) {
    /*!re2c
        re2c:api = generic;
        re2c:YYPEEK = "$cur < $lim ? ord($cur) : 0;";
        re2c:YYSKIP = "$cur += 1;";
        re2c:yyfill:enable = 0;

        *      { return -1; }
        [\x00] { return $count; }
        [ ]+   { break 2; }
        [a-z]+ { $count += 1; break 2; }
    */
    }
}

function test($s, $n) {
    if (lex($s) != $n) {
        throw new \Exception("error!");
    }
}

test("", 0);
test("one two three", 3);
test("f0ur", -1);
