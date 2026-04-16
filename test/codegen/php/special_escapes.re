// re2php $INPUT -o $OUTPUT
<?php

function lex($yyinput) {
    $yycursor = 0;
    $yymarker = 0;
    /*!re2c
        re2c:yyfill:enable = 0;

        "\a\b\f\n\r\t\v\\'\"" { return true; }
        * {
            $x = ['\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\', '\'', '\"']; // unused
            return false;
        }
    */
}

if (!lex("\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"\0")) {
    throw new \Exception("error!");
}
