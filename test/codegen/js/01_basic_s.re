// re2js $INPUT -o $OUTPUT -s

function lex(str) {
    let cur = 0
    /*!re2c
        re2c:api = custom;
        re2c:define:YYPEEK = "str.charCodeAt(cur)";
        re2c:define:YYSKIP = "cur += 1";
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return true }
        *      { return false }
    */
}

if (!lex("1234\0")) {
    throw "error!"
}
