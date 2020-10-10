/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *s1, *u1, *h1, *r1, *p1, *q1, *f1,
        *s2, *u2, *h2, *r2, *p2, *q2, *f2;

loop:
    in->tok = in->cur;
/*!re2c
    end       = "\x00";
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

    *   { return 1; }
    end { return 0; }
    uri {
        OUT("scheme: ", s1, s2);
        if (u1) OUT("user: ", u1, u2);
        if (h1) OUT("host: ", h1, h2);
        if (r1) OUT("port: ", r1, r2);
        OUT("path: ", p1, p2);
        if (q1) OUT("query: ", q1, q2);
        if (f1) OUT("fragment: ", f1, f2);
        outc(out, '\n');
        goto loop;
    }
*/
}
