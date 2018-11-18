/*!header:re2c:1*/
bool lex(const char *);
/*!header:re2c:0*/

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
