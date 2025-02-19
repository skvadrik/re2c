#include "re2c/base.h"

namespace re2c_lex_00__numbers1 {

/*!rules:re2c:main
    [0-9]+ [\n] {
        OUTS(YYTOKEN, YYCURSOR);
        goto loop;
    }
    * { return -1; }
*/

/*!include:re2c "base.re" */

} // namespace re2c_lex_00__numbers1

