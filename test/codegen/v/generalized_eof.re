// re2v $INPUT -o $OUTPUT -i

/*!rules:re2c:x
    $           { return 0 }
    *           { return 1 }
    [a] $       { return 2 }
    [a]         { return 3 }
    [b] $ | [b] { return 4 }
    [c]+ $      { return 5 }
*/

fn lex_simple(yyinput string) int {
    mut yycursor := 0
    mut yymarker := 0
    yylimit := yyinput.len - 1

    /*!use:re2c:x
        re2c:yyfill:enable = 0;
    */
}

fn lex_eof(yyinput string) int {
    mut yycursor := 0
    mut yymarker := 0
    yylimit := yyinput.len - 1

    /*!use:re2c:x
        re2c:eof = 0;
        re2c:YYFILL = "false";
        re2c:YYEND = "yycursor == yylimit";
    */
}

/*!max:re2c*/

fn lex_scc(str string) int {
    mut yycursor := 0
    mut yymarker := 0
    end := str.len - 1
    yylimit := end + yymaxfill

    mut yyinput := []u8{len: yylimit}
    copy(mut &yyinput, str.bytes())

    /*!use:re2c:x
        re2c:YYFILL = "return -1";
        re2c:YYEND = "yycursor == end";
    */
}

fn test(str string, ret int) {
    assert lex_simple(str) == ret
    assert lex_eof(str) == ret
    assert lex_scc(str) == ret
}

fn main() {
    test("\0", 0)
    test("a\0", 2)
    test("ax\0", 3)
    test("b\0", 4)
    test("bx\0", 4)
    test("ccc\0", 5)
}
