/*!include:re2c "common.re" */

static const char *print(Output *out, const char *tok, const taglist_t *t)
{
    if (!t) return tok;

    const char *s = print(out, tok, t->pred);
    const char *e = tok + t->dist;
    outs(out, s, e);
    outc(out, '.');
    return e;
}

static int lex(input_t *in, Output *out)
{
    taglist_t *t = NULL;

loop:
    in->tok = in->cur;
/*!use:re2c
    aaa = ([a]{64} #t)*;

    *         { return 1; }
    aaa [\n] {
        print(out, in->tok, t);
        outc(out, '\n');
        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
*/
}
