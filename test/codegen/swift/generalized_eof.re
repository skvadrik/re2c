// re2swift $INPUT -o $OUTPUT -i

/*!rules:re2c:x
    $           { return 0 }
    *           { return 1 }
    [a] $       { return 2 }
    [a]         { return 3 }
    [b] $ | [b] { return 4 }
    [c]+ $      { return 5 }
*/

func lex_simple(_ str: StaticString) -> Int {
    let yyinput = str.utf8Start
    let yylimit = str.utf8CodeUnitCount
    var yycursor = 0
    var yymarker = 0
    /*!use:re2c:x
      re2c:yyfill:enable = 0;
    */
}

func lex_eof(_ str: StaticString) -> Int {
    let yyinput = str.utf8Start
    let yylimit = str.utf8CodeUnitCount
    var yycursor = 0
    var yymarker = 0
    /*!use:re2c:x
      re2c:eof = 0;
      re2c:YYFILL = "false";
      re2c:YYEND = "yycursor == yylimit";
    */
}

/*!max:re2c*/

func lex_scc(_ str: StaticString) -> Int {
    let yyinput =  str.withUTF8Buffer {
        ContiguousArray<UInt8>($0) + repeatElement(0, count: yymaxfill)
    }
    let end = str.utf8CodeUnitCount
    let yylimit = end + yymaxfill
    var yycursor = 0
    var yymarker = 0
    /*!use:re2c:x
      re2c:YYFILL = "return -1";
      re2c:YYEND = "yycursor == end";
    */
}

func test(_ s: StaticString, _ r: Int) {
    assert(lex_simple(s) == r)
    assert(lex_eof(s) == r)
    assert(lex_scc(s) == r)
}

test("", 0)
test("a", 2)
test("ax", 3)
test("b", 4)
test("bx", 4)
test("ccc", 5)
