#include "re2c/base.h"

namespace re2c_lex_02__words1 {

/*!rules:re2c:main
    word
        = "Monday"
        | "Tuesday"
        | "Wednesday"
        | "Thursday"
        | "Friday"
        | "Saturday"
        | "Sunday"
        ;
    word [\n] {
        OUTS(YYTOKEN, YYCURSOR);
        goto loop;
    }
    * { return -1; }
*/

/*!include:re2c "base.re" */

} // namespace re2c_lex_02__words1

