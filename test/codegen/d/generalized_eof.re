// re2d $INPUT -o $OUTPUT -i

import core.stdc.stdlib;
import core.stdc.string;

/*!max:re2c*/

/*!rules:re2c:x
    re2c:YYCTYPE = char;
    re2c:api:style = free-form;

    $           { return 0; }
    *           { return 1; }
    [a] $       { return 2; }
    [a]         { return 3; }
    [b] $ | [b] { return 4; }
    [c]+ $      { return 5; }
*/

private int lex_simple(immutable char[] str) {
    const(char)* yycursor = cast(char*)str;
    const(char)* yylimit = yycursor + str.length;;
    const(char)* yymarker;

    /*!use:re2c:x
        re2c:yyfill:enable = 0;
    */
}

private int lex_eof(immutable char[] str) {
    const(char)* yycursor = cast(char*)str;
    const(char)* yylimit = yycursor + str.length;
    const(char)* yymarker;

    /*!use:re2c:x
        re2c:eof = 0;
        re2c:YYFILL = "0"; // always fails
        re2c:YYEND = "yycursor == yylimit";
    */
}

private int lex_scc(immutable char[] str) {
    static char[256] buf;
    char* yycursor = cast(char*)buf;
    char* end = yycursor + str.length;
    char* yylimit = end + YYMaxFill;
    char* yymarker;

    memcpy(cast(void*)buf, cast(const(void*))str, str.length);
    memset(end, 0, YYMaxFill);

    /*!use:re2c:x
        re2c:YYFILL = "return -1;"; // always fails
        re2c:YYEND = "yycursor == end";
    */
}

private void test(immutable char[] str, int ret) {
    assert(lex_simple(str) == ret);
    assert(lex_eof(str) == ret);
    assert(lex_scc(str) == ret);
}

void main() {
    test("", 0);
    test("a", 2);
    test("ax", 3);
    test("b", 4);
    test("bx", 4);
    test("ccc", 5);
}
