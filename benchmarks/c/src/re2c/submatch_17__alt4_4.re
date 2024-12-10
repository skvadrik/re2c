#include "re2c/base.h"

namespace re2c_submatch_17__alt4_4 {

/*!rules:re2c:main
    * { return -1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    | (@c1 [c]* @c2)
    | (@d1 [d]* @d2)
    )
    ( (@a3 [a]* @a4)
    | (@b3 [b]* @b4)
    | (@c3 [c]* @c4)
    | (@d3 [d]* @d4)
    )
    ( (@a5 [a]* @a6)
    | (@b5 [b]* @b6)
    | (@c5 [c]* @c6)
    | (@d5 [d]* @d6)
    )
    ( (@a7 [a]* @a8)
    | (@b7 [b]* @b8)
    | (@c7 [c]* @c8)
    | (@d7 [d]* @d8)
    )
    [\n] {
        if (a1)      { OUTC('A'); OUTS(a1, a2); }
        else if (b1) { OUTC('B'); OUTS(b1, b2); }
        else if (c1) { OUTC('C'); OUTS(c1, c2); }
        else if (d1) { OUTC('D'); OUTS(d1, d2); }
        if (a3)      { OUTC('A'); OUTS(a3, a4); }
        else if (b3) { OUTC('B'); OUTS(b3, b4); }
        else if (c3) { OUTC('C'); OUTS(c3, c4); }
        else if (d3) { OUTC('D'); OUTS(d3, d4); }
        if (a6)      { OUTC('A'); OUTS(a5, a6); }
        else if (b6) { OUTC('B'); OUTS(b5, b6); }
        else if (c6) { OUTC('C'); OUTS(c5, c6); }
        else if (d6) { OUTC('D'); OUTS(d5, d6); }
        if (a8)      { OUTC('A'); OUTS(a7, a8); }
        else if (b8) { OUTC('B'); OUTS(b7, b8); }
        else if (c8) { OUTC('C'); OUTS(c7, c8); }
        else if (d8) { OUTC('D'); OUTS(d7, d8); }
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_17__alt4_4
