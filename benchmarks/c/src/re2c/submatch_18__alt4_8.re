#include "re2c/base.h"

namespace re2c_submatch_18__alt4_8 {

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
    ( (@a3 [a]* @a4)
    | (@b3 [b]* @b4)
    | (@c3 [c]* @c4)
    | (@d3 [d]* @d4)
    | (@e3 [e]* @e4)
    | (@f3 [f]* @f4)
    | (@g3 [g]* @g4)
    | (@h3 [h]* @h4)
    )
    ( (@a5 [a]* @a6)
    | (@b5 [b]* @b6)
    | (@c5 [c]* @c6)
    | (@d5 [d]* @d6)
    | (@e5 [e]* @e6)
    | (@f5 [f]* @f6)
    | (@g5 [g]* @g6)
    | (@h5 [h]* @h6)
    )
    ( (@a7 [a]* @a8)
    | (@b7 [b]* @b8)
    | (@c7 [c]* @c8)
    | (@d7 [d]* @d8)
    | (@e7 [e]* @e8)
    | (@f7 [f]* @f8)
    | (@g7 [g]* @g8)
    | (@h7 [h]* @h8)
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
        if (a3)      { OUTC('A'); OUTS(a3, a4); }
        else if (b3) { OUTC('B'); OUTS(b3, b4); }
        else if (c3) { OUTC('C'); OUTS(c3, c4); }
        else if (d3) { OUTC('D'); OUTS(d3, d4); }
        else if (e3) { OUTC('E'); OUTS(e3, e4); }
        else if (f3) { OUTC('F'); OUTS(f3, f4); }
        else if (g3) { OUTC('G'); OUTS(g3, g4); }
        else if (h3) { OUTC('H'); OUTS(h3, h4); }
        if (a6)      { OUTC('A'); OUTS(a5, a6); }
        else if (b6) { OUTC('B'); OUTS(b5, b6); }
        else if (c6) { OUTC('C'); OUTS(c5, c6); }
        else if (d6) { OUTC('D'); OUTS(d5, d6); }
        else if (e6) { OUTC('E'); OUTS(e5, e6); }
        else if (f6) { OUTC('F'); OUTS(f5, f6); }
        else if (g6) { OUTC('G'); OUTS(g5, g6); }
        else if (h6) { OUTC('H'); OUTS(h5, h6); }
        if (a8)      { OUTC('A'); OUTS(a7, a8); }
        else if (b8) { OUTC('B'); OUTS(b7, b8); }
        else if (c8) { OUTC('C'); OUTS(c7, c8); }
        else if (d8) { OUTC('D'); OUTS(d7, d8); }
        else if (e8) { OUTC('E'); OUTS(e7, e8); }
        else if (f8) { OUTC('F'); OUTS(f7, f8); }
        else if (g8) { OUTC('G'); OUTS(g7, g8); }
        else if (h8) { OUTC('H'); OUTS(h7, h8); }
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_18__alt4_8
