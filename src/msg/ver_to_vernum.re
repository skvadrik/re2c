#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <string>

#include "config.h"
#include "src/msg/ver_to_vernum.h"


namespace re2c {

std::string ver_to_vernum(const char *ver)
{
#define YYCTYPE char
    const char *YYCURSOR = ver, *YYMARKER,
        *p1, *p2, *p3, *e1, *e2, *e3;

/*!re2c re2c:flags:tags = 1; */
/*!stags:re2c format = "const char *@@;\n"; */
/*!re2c
    re2c:yyfill:enable = 0;

    dot = [.];
    num = [0-9]{1,2};
    end = [\x00];
    sfx = [a-z]+;

    @p1 num @e1
        (dot @p2 num @e2
            (dot @p3 num @e3
                (dot num)*
            )?
        )?
    (dot sfx)? end {

        static const uint32_t PARTS = 3, WIDTH = 2, SIZE = PARTS * WIDTH;
        char buffer[SIZE], *q, *q0;
        const char * bounds[] = {p1, e1, p2, e2, p3, e3}, *p, *p0;

        for (uint32_t i = 0; i < PARTS; ++i) {
            q0 = buffer + 2 * i;
            q  = buffer + 2 * (i + 1);
            p0 = bounds[2 * i];
            p  = bounds[2 * i + 1];
            while (p > p0) *--q = *--p;
            while (q > q0) *--q = '0';
        }

        return std::string(buffer, SIZE);
    }

    * { return std::string(); }
*/
#undef YYCTYPE
}

} // namespace re2c
