/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a0, *a1, *a2, *a3,
        *b0, *b1, *b2, *b3;
loop:
    in->tok = in->cur;
/*!use:re2c
    * { return 1; }

    @a0 [a]* @b0 [b]*
    @a1 [a]* @b1 [b]*
    @a2 [a]* @b2 [b]*
    @a3 [a]* @b3 [b]*
    [\n] {
        outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
        outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
        outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
        outs(out, a3, b3); outc(out, '.'); outs(out, b3, in->cur);
        goto loop;
    }
*/
}
