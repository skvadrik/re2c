#include "re2c/base.h"

namespace re2c_vec_02__uri_simple {

/*!rules:re2c:main
    nl        = "\n";
    char      = [-._~%!$&'()*+,;=a-zA-Z0-9];
    scheme    = @s1 [-+.a-zA-Z0-9]+ @s2;
    userinfo  = @u1 (char | [:])+ @u2;
    host      = @h1 (char | "[" (char | [:])* "]")+ @h2;
    port      = @r1 [0-9]* @r2;
    path      = @p1 (char | [:@/])* @p2;
    query     = @q1 (char | [:@?/])* @q2;
    fragment  = @f1 (char | [:@?/])* @f2;
    uri       = scheme ":"
                ("//" (userinfo "@")? host (":" port)?)?
                path ("?" query)? ("#" fragment)? nl;

    *   { return -1; }
    uri {
        SUBMATCH(1, s1, s2);
        if (u1) SUBMATCH(2, u1, u2);
        if (h1) SUBMATCH(3, h1, h2);
        if (r1) SUBMATCH(4, r1, r2);
        SUBMATCH(5, p1, p2);
        if (q1) SUBMATCH(6, q1, q2);
        if (f1) SUBMATCH(7, f1, f2);
        goto loop;
    }
*/

/*!include:re2c "vec_base.re" */

} // namespace re2c_vec_02__uri_simple
