#include "re2c/base.h"

namespace re2c_submatch_27__cat8_1 {

/*!rules:re2c:main
    * { return -1; }

    @a0 [a]* @b0 [a][b]*
    @a1 [a]* @b1 [a][b]*
    @a2 [a]* @b2 [a][b]*
    @a3 [a]* @b3 [a][b]*
    @a4 [a]* @b4 [a][b]*
    @a5 [a]* @b5 [a][b]*
    @a6 [a]* @b6 [a][b]*
    @a7 [a]* @b7 [a][b]*
    [\n] {
        OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
        OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
        OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
        OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
        OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
        OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
        OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
        OUTS(a7, b7); OUTC('.'); OUTS(b7, in->cur);
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_27__cat8_1
