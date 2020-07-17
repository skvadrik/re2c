// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
/*!include:re2c "definitions.h" */

Result lex(const char *YYCURSOR)
{
    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;

    number { return OK; }
    *      { return FAIL; }
    */
}

int main()
{
    assert(lex("123") == OK);
    return 0;
}
