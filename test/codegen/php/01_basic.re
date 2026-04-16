// re2php $INPUT -o $OUTPUT
<?php

function lex($yyinput) {
    $yycursor = 0;
    /*!re2c
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return true; }
        *      { return false; }
    */
}

if (!lex("1234\0")) {
    throw new \Exception("error!");
}
