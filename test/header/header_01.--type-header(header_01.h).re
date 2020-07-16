// re2c $INPUT -o $OUTPUT  --type-header header_01.h
/*!header:re2c:on*/
bool lex(const char *);
/*!header:re2c:off*/

#include "header_01.h"

bool lex(const char *YYCURSOR)
{
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        "a" { return true; }
        *   { return false; }
    */
}
