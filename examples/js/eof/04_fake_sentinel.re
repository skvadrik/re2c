// re2js $INPUT -o $OUTPUT

// expects a string without terminating null
function lex(str) {
    var cur = 0;
    var lim = str.length
    var count = 0

    loop: while (true) {
    /*!re2c
        re2c:api = custom;
        re2c:define:YYPEEK = "cur < lim ? str.charCodeAt(cur) : 0";
        re2c:define:YYSKIP = "cur += 1";
        re2c:yyfill:enable = 0;

        *      { return -1 }
        [\x00] { return count }
        [ ]+   { continue loop }
        [a-z]+ { count += 1; continue loop }
    */
    }
}

function test(s, n) { if (lex(s) != n) throw "error!"; }
test("", 0)
test("one two three", 3)
test("f0ur", -1)
