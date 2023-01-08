// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
/*!include:re2c "definitions.h" */

Result lex(const char *s) {
    const char *YYCURSOR = s, *YYMARKER;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        *      { return FAIL; }
        number { return OK; }
        !include "extra_rules.re.inc";
    */
}

int main() {
    assert(lex("123") == OK);
    assert(lex("123.4567") == OK);
    return 0;
}
