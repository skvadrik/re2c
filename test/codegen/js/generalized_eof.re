// re2js $INPUT -o $OUTPUT -i

/*!max:re2c*/

/*!rules:re2c:x
    $           { return 0 }
    *           { return 1 }
    [a] $       { return 2 }
    [a]         { return 3 }
    [b] $ | [b] { return 4 }
    [c]+ $      { return 5 }
*/

function lex_simple(yyinput) {
    let yycursor = 0
    let yymarker = 0
    let yylimit = yyinput.length - 1
    /*!use:re2c:x
        re2c:yyfill:enable = 0;
    */
}

function lex_eof(yyinput) {
    let yycursor = 0
    let yymarker = 0
    let yylimit = yyinput.length - 1
    /*!use:re2c:x
        re2c:eof = 0;
        re2c:YYFILL = "false"; // always fails
        re2c:YYEND = "yycursor === yylimit";
    */
}

function lex_scc(str) {
    let yyinput = str + "\0".repeat(YYMAXFILL)
    let yycursor = 0
    let yymarker = 0
    let yylimit = yyinput.length
    let end = str.length - 1
    /*!use:re2c:x
        re2c:YYFILL = "return -1"; // always fails
        re2c:YYEND = "yycursor == end";
    */
}

function test(str, ret) {
    if (lex_simple(str) != ret) throw "error simple"
    if (lex_eof(str) != ret) throw "error eof"
    if (lex_scc(str) != ret) throw "error scc"
}

test("\0", 0)
test("a\0", 2)
test("ax\0", 3)
test("b\0", 4)
test("bx\0", 4)
test("ccc\0", 5)
