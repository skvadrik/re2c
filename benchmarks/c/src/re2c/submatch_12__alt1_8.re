#include "re2c/base.h"

namespace re2c_submatch_12__alt1_8 {

/*!rules:re2c:main
    * { return -1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    | (@c1 [c]* @c2)
    | (@d1 [d]* @d2)
    | (@e1 [e]* @e2)
    | (@f1 [f]* @f2)
    | (@g1 [g]* @g2)
    | (@h1 [h]* @h2)
    )
    [\n] {
        if (a1)      { OUTC('A'); OUTS(a1, a2); }
        else if (b1) { OUTC('B'); OUTS(b1, b2); }
        else if (c1) { OUTC('C'); OUTS(c1, c2); }
        else if (d1) { OUTC('D'); OUTS(d1, d2); }
        else if (e1) { OUTC('E'); OUTS(e1, e2); }
        else if (f1) { OUTC('F'); OUTS(f1, f2); }
        else if (g1) { OUTC('G'); OUTS(g1, g2); }
        else if (h1) { OUTC('H'); OUTS(h1, h2); }
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_12__alt1_8
