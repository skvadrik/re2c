/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *h1, *i1, *a1, *d1, *r1, *s1, *z1, *u1, *g1,
        *h2, *i2, *a2, *d2, *r2, *s2, *z2, *u2, *g2;

loop:
    in->tok = in->cur;
/*!re2c
    end       = "\x00";
    sp        = [ \t]+;
    host      = @h1 [0-9.]+ @h2;
    userid    = @i1 [-] @i2;
    authuser  = @a1 [-] @a2;
    date      = @d1 "[" [^\n\]]+ "]" @d2;
    request   = @r1 ["] [^\n"]+ ["] @r2;
    status    = @s1 [0-9]+ @s2;
    size      = @z1 ([0-9]+ | '-') @z2;
    url       = @u1 ["] [^\n"]* ["] @u2;
    useragent = @g1 ["] [^\n"]* ["] @g2;
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

    *    { return 1; }
    end  { return 0; }
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
        outc(out, '\n');
        goto loop;
    }
*/
}
