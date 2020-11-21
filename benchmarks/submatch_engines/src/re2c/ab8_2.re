/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
        *b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
loop:
    in->tok = in->cur;
/*!use:re2c
    * { return 1; }

    @a0 [a]* @b0 [a][a][b]*
    @a1 [a]* @b1 [a][a][b]*
    @a2 [a]* @b2 [a][a][b]*
    @a3 [a]* @b3 [a][a][b]*
    @a4 [a]* @b4 [a][a][b]*
    @a5 [a]* @b5 [a][a][b]*
    @a6 [a]* @b6 [a][a][b]*
    @a7 [a]* @b7 [a][a][b]*
    [\n] {
        outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
        outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
        outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
        outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
        outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
        outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
        outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
        outs(out, a7, b7); outc(out, '.'); outs(out, b7, in->cur);
        goto loop;
    }
*/
}
