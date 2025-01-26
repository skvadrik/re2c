#include "re2c/base.h"

namespace re2c_submatch_07__ipv4 {

/*!rules:re2c:main
    oct  = [0-9]{1,3};
    dot  = [.];
    ipv4 = @p1 oct dot @p2 oct dot @p3 oct dot @p4 oct [\n];

    *    { return -1; }
    ipv4 {
        OUTS(p1, p2 - 1);
        OUTC(',');
        OUTS(p2, p3 - 1);
        OUTC(',');
        OUTS(p3, p4 - 1);
        OUTC(',');
        OUTS(p4, YYCURSOR - 1);
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_07__ipv4

