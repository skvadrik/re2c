// re2c $INPUT -o $OUTPUT  --type-header header_03.h
/*!re2c re2c:flags:type-header = "header_03.h"; */

/*!header:re2c:on*/
#define YYCTYPE char
void lex(const YYCTYPE *);
/*!header:re2c:off*/

#include "header_03.h"

void lex(const YYCTYPE *YYCURSOR)
{
    /*!re2c
        re2c:yyfill:enable = 0;
        * { return; }
    */
}
