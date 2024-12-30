<?php
// re2php $INPUT -o $OUTPUT

// expects a null-terminated string
function lex($yyinput) {
    $yycursor = 0;
    $yylimit = strlen($yyinput) - 1; // terminating null not included
    $count = 0;

    while (true) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return $count; }
        [ ]+ { break 2; }
        str  { $count += 1; break 2; }
    */
    }
}

function test($s, $n) {
    if (lex($s) != $n) {
        throw new \Exception("error!");
    }
}

test("\0", 0);
test("'qu\0tes' 'are' 'fine: \\'' \0", 3);
test("'unterminated\\'\0", -1);
