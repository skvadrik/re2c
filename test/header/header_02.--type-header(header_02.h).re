// re2c $INPUT -o $OUTPUT  --type-header header_02.h
/*!re2c re2c:flags:tags = 1; */

/*!header:re2c:on*/
#define YYCTYPE char
struct tags_t
{
    /*!stags:re2c format = "const YYCTYPE * @@;"; */
};

void lex(const YYCTYPE *, tags_t &);
/*!header:re2c:off*/

#include "header_02.h"

void lex(const YYCTYPE *s, tags_t &tags)
{
    const YYCTYPE *YYCURSOR = s, *x, *y;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:tags:expression = "tags.@@";

        "a"* @x "b"* @y "c"* { return; }
    */
}
