#include "re2c/base.h"

namespace re2c_submatch_26__cat8_0 {

/*!rules:re2c:main
    * { return -1; }

    @a0 [a]* @b0 [b]*
    @a1 [a]* @b1 [b]*
    @a2 [a]* @b2 [b]*
    @a3 [a]* @b3 [b]*
    @a4 [a]* @b4 [b]*
    @a5 [a]* @b5 [b]*
    @a6 [a]* @b6 [b]*
    @a7 [a]* @b7 [b]*
    [\n] {
        OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
        OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
        OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
        OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
        OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
        OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
        OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
        OUTS(a7, b7); OUTC('.'); OUTS(b7, YYCURSOR);
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_26__cat8_0
