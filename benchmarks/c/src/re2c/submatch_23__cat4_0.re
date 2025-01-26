#include "re2c/base.h"

namespace re2c_submatch_23__cat4_0 {

/*!rules:re2c:main
    * { return -1; }

    @a0 [a]* @b0 [b]*
    @a1 [a]* @b1 [b]*
    @a2 [a]* @b2 [b]*
    @a3 [a]* @b3 [b]*
    [\n] {
        OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
        OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
        OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
        OUTS(a3, b3); OUTC('.'); OUTS(b3, YYCURSOR);
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_23__cat4_0
