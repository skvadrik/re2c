#include "re2c/base.h"

namespace re2c_submatch_04__apache_log {

/*!rules:re2c:main
    sp        = [ \t]+;
    host      = @h1 [0-9.]+ @h2;
    userid    = @i1 [-] @i2;
    authuser  = @a1 [-] @a2;
    date      = @d1 "[" [^\x00\n\]]+ "]" @d2;
    request   = @r1 ["] [^\x00\n"]+ ["] @r2;
    status    = @s1 [0-9]+ @s2;
    size      = @z1 ([0-9]+ | '-') @z2;
    url       = @u1 ["] [^\x00\n"]* ["] @u2;
    useragent = @g1 ["] [^\x00\n"]* ["] @g2;
    line    =
        host      sp
        userid    sp
        authuser  sp
        date      sp
        request   sp
        status    sp
        size      sp
        url       sp
        useragent [\n];

    *    { return -1; }
    line {
        OUT("host: ",     h1, h2);
        OUT("userid: ",   i1, i2);
        OUT("authuser: ", a1, a2);
        OUT("date: ",     d1, d2);
        OUT("request: ",  r1, r2);
        OUT("status: ",   s1, s2);
        OUT("size: ",     z1, z2);
        OUT("url: ",      u1, u2);
        OUT("agent: ",    g1, g2);
        OUTC('\n');
        goto loop;
    }
*/

/*!include:re2c "base.re" */

} // namespace re2c_submatch_04__apache_log
