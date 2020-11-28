/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a1, *b1, *c1, *d1,
        *a2, *b2, *c2, *d2,
        *a3, *b3, *c3, *d3,
        *a4, *b4, *c4, *d4;
loop:
    in->tok = in->cur;
/*!use:re2c
    * { return 1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    | (@c1 [c]* @c2)
    | (@d1 [d]* @d2)
    )
    ( (@a3 [a]* @a4)
    | (@b3 [b]* @b4)
    | (@c3 [c]* @c4)
    | (@d3 [d]* @d4)
    )
    [\n] {
        if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
        else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
        else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
        else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
        if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
        else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
        else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
        else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
        outc(out, '\n');
        goto loop;
    }
*/
}
