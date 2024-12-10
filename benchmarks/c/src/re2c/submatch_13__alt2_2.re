#include "re2c/base.h"

namespace re2c_submatch_13__alt2_2 {

/*!rules:re2c:main
    * { return -1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    )
    ( (@a3 [a]* @a4)
    | (@b3 [b]* @b4)
    )
    [\n] {
        if (a1)      { OUTC('A'); OUTS(a1, a2); }
        else if (b1) { OUTC('B'); OUTS(b1, b2); }
        if (a3)      { OUTC('A'); OUTS(a3, a4); }
        else if (b3) { OUTC('B'); OUTS(b3, b4); }
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_13__alt2_2
