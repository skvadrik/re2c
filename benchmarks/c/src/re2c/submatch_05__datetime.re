#include "re2c/base.h"

namespace re2c_submatch_05__datetime {

/*!rules:re2c:main
    year     = @y1 (([1-9][0-9]*)? [0-9]{4}) @y2;
    month    = @m1 ([1][0-2] | [0][1-9]) @m2;
    day      = @d1 ([3][0-1] | [0][1-9] | [1-2][0-9]) @d2;
    hours    = @h1 ([2][0-3] | [0-1][0-9]) @h2;
    minutes  = @M1 [0-5][0-9] @M2;
    seconds  = @s1 [0-5][0-9] @s2;
    timezone = @z1 ([Z] | [+-]([2][0-3] | [0-1][0-9])[:][0-5][0-9]) @z2;
    datetime = year [-] month [-] day [T] hours [:] minutes [:] seconds timezone [\n];

    *        { return -1; }
    datetime {
        OUT("year: ",    y1, y2);
        OUT("month: ",   m1, m2);
        OUT("day: ",     d1, d2);
        OUT("hours: ",   h1, h2);
        OUT("minutes: ", M1, M2);
        OUT("seconds: ", s1, s2);
        OUT("tz: ",      z1, z2);
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_05__datetime
