/*!include:re2c "common.re" */

static const char *print(Output *out, const char *tok, const char *start,
    const taglist_t *t)
{
    if (!t) return start;

    const char *s = print(out, tok, start, t->pred);
    if (t->dist > 0) {
        const char *e = tok + t->dist;
        outs(out, s, e);
        outc(out, '.');
        return e;
    } else {
        return s;
    }
}

static int lex(input_t *in, Output *out)
{
    taglist_t *t1 = NULL, *t2 = NULL, *t3 = NULL;

loop:
    in->tok = in->cur;
/*!use:re2c
    aaa = ([a]{13} #t1)* ([a]{11} #t2)* ([a]{7} #t3)*;

    *         { return 1; }
    aaa [\n] {
        const char *p = in->tok;
        p = print(out, in->tok, p, t1);
        p = print(out, in->tok, p, t2);
        p = print(out, in->tok, p, t3);
        outc(out, '\n');
        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
*/
}
