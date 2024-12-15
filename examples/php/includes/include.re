// re2js $INPUT -o $OUTPUT

/*!include:re2c "definitions.js" */

function lex(yyinput) {
    let yycursor = 0
    /*!re2c
        re2c:yyfill:enable = 0;

        *      { return NAN }
        number { return INT }
        !include "extra_rules.re.inc";
    */
}

function test(s, n) {
    if (lex(s) != n) throw "error!"
}

test("123\0", INT)
test("123.4567\0", FLOAT)
