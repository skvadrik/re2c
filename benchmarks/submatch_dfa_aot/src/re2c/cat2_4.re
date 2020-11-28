/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a0, *a1,
        *b0, *b1;
loop:
    in->tok = in->cur;
/*!use:re2c
    * { return 1; }

    @a0 [a]* @b0 [a]{4}[b]*
    @a1 [a]* @b1 [a]{4}[b]*
    [\n] {
        outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
        outs(out, a1, b1); outc(out, '.'); outs(out, b1, in->cur);
        goto loop;
    }
*/
}
