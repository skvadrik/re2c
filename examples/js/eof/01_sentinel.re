// re2js $INPUT -o $OUTPUT

// expects a null-terminated string
function lex(yyinput) {
    let yycursor = 0;
    let count = 0

    loop: while (true) {
    /*!re2c
        re2c:yyfill:enable = 0;

        *      { return -1 }
        [\x00] { return count }
        [ ]+   { continue loop }
        [a-z]+ { count += 1; continue loop }
    */
    }
}

function test(s, n) { if (lex(s) != n) throw "error!"; }
test("\0", 0)
test("one two three\0", 3)
test("f0ur\0", -1)
