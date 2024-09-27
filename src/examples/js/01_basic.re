// re2js $INPUT -o $OUTPUT

function lex(yyinput) {
    let yycursor = 0;
    /*!re2c
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return true; }
        *      { return false; }
    */
}

if (!lex("1234\0")) {
    throw "error!"
}
