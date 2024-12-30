<?php
// re2php $INPUT -o $OUTPUT

// expects a null-terminated string
function lex($yyinput) {
    $yycursor = 0;
    $count = 0;

    while (true) {
    /*!re2c
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

test("\0", 0);
test("one two three\0", 3);
test("f0ur\0", -1);
