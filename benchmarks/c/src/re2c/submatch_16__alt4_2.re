#include "re2c/base.h"

namespace re2c_submatch_16__alt4_2 {

/*!rules:re2c:main
    * { return -1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    )
    ( (@a3 [a]* @a4)
    | (@b3 [b]* @b4)
    )
    ( (@a5 [a]* @a6)
    | (@b5 [b]* @b6)
    )
    ( (@a7 [a]* @a8)
    | (@b7 [b]* @b8)
    )
    [\n] {
        if (a1)      { OUTC('A'); OUTS(a1, a2); }
        else if (b1) { OUTC('B'); OUTS(b1, b2); }
        if (a3)      { OUTC('A'); OUTS(a3, a4); }
        else if (b3) { OUTC('B'); OUTS(b3, b4); }
        if (a6)      { OUTC('A'); OUTS(a5, a6); }
        else if (b6) { OUTC('B'); OUTS(b5, b6); }
        if (a8)      { OUTC('A'); OUTS(a7, a8); }
        else if (b8) { OUTC('B'); OUTS(b7, b8); }
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_16__alt4_2
