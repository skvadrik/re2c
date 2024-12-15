// re2js $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
    re2c:yyfill:enable = 0;
    re2c:YYPEEK = "at";

    "∀x ∃y" { return yycursor }
    *       { return null }
*/

function lex_utf8(yyinput) {
    let yycursor = 0
    /*!use:re2c
        re2c:encoding:utf8 = 1;
    */
}

function lex_utf32(yyinput) {
    let yycursor = 0
    /*!use:re2c
        re2c:encoding:utf32 = 1;
    */
}

function test(f, s) {
    if (f(s) != s.length) throw "error!"
}

test(lex_utf8, [0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79])
test(lex_utf32, [0x2200, 0x78, 0x20, 0x2203, 0x79])
