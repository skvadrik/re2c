// re2js $INPUT -o $OUTPUT

// expects a null-terminated string
function lex(yyinput) {
    let yycursor = 0;
    let yylimit = yyinput.length - 1 // terminating null not included
    let count = 0

    loop: while (true) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1 }
        $    { return count }
        [ ]+ { continue loop }
        str  { count += 1; continue loop }
    */
    }
}

function test(s, n) { if (lex(s) != n) throw "error!"; }
test("\0", 0)
test("'qu\0tes' 'are' 'fine: \\'' \0", 3)
test("'unterminated\\'\0", -1)
