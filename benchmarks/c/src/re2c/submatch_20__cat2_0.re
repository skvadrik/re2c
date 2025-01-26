#include "re2c/base.h"

namespace re2c_submatch_20__cat2_0 {

/*!rules:re2c:main
    * { return -1; }

    @a0 [a]* @b0 [b]*
    @a1 [a]* @b1 [b]*
    [\n] {
        OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
        OUTS(a1, b1); OUTC('.'); OUTS(b1, YYCURSOR);
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_20__cat2_0
