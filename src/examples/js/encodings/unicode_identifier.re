// re2js $INPUT -o $OUTPUT --utf8 -s

/*!include:re2c "unicode_categories.re" */

function lex(yyinput) {
    let yycursor = 0
    /*!re2c
        re2c:yyfill:enable = 0;

        // Simplified "Unicode Identifier and Pattern Syntax"
        // (see https://unicode.org/reports/tr31)
        id_start    = L | Nl | [$_];
        id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
        identifier  = id_start id_continue*;

        identifier { return true }
        *          { return false }
    */
}

if (!lex("_Ыдентификатор\0")) throw "error!"
