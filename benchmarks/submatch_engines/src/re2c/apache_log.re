/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char *h2,
        *d1, *r1, *s1, *z1, *l1, *a1,
        *d2, *r2, *s2, *z2, *l2, *a2;

    outc(out, '[');

loop:
    in->tok = in->cur;
/*!re2c
    end = "\x00";

    host    = [0-9.]+ @h2;
    user    = [a-zA-Z]+;
    date    = @d1 [^\]]+ @d2;
    request = @r1 [^"]+ @r2;
    status  = @s1 [0-9]+ @s2;
    size    = @z1 ([0-9]+ | [-]) @z2;
    url     = @l1 [^"]* @l2;
    agent   = @a1 [^"]* @a2;
    space   = [ ];
    line    =
        host            space
        [-]             space
        [-]             space
        "[" date "]"    space
        ["] request ["] space
        status          space
        size            space
        ["] url ["]     space
        ["] agent ["]   [\n];

    * { return 1; }
    end {
        out->pos -= 2;
        outstr(out, "\n]\n");
        return 0;
    }
    line {
        outstr(out, "{\"host\":\"");
        outs(out, in->tok, h2);
        outstr(out, "\",\"date\":\"");
        outs(out, d1, d2);
        outstr(out, "\",\"request\":\"");
        outs(out, r1, r2);
        outstr(out, "\",\"status\":\"");
        outs(out, s1, s2);
        outstr(out, "\",\"size\":\"");
        outs(out, z1, z2);
        outstr(out, "\",\"url\":\"");
        outs(out, l1, l2);
        outstr(out, "\",\"agent\":\"");
        outs(out, a1, a2);
        outstr(out, "\"},\n");
        goto loop;
    }
*/
}
