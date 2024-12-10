#include "re2c/base.h"

namespace re2c_submatch_10__alt1_2 {

/*!rules:re2c:main
    * { return -1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    )
    [\n] {
        if (a1)      { OUTC('A'); OUTS(a1, a2); }
        else if (b1) { OUTC('B'); OUTS(b1, b2); }
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_10__alt1_2
