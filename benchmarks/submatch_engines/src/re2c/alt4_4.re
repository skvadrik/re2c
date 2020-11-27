/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a1, *b1, *c1, *d1,
        *a2, *b2, *c2, *d2,
        *a3, *b3, *c3, *d3,
        *a4, *b4, *c4, *d4,
        *a5, *b5, *c5, *d5,
        *a6, *b6, *c6, *d6,
        *a7, *b7, *c7, *d7,
        *a8, *b8, *c8, *d8;
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
    ( (@a5 [a]* @a6)
    | (@b5 [b]* @b6)
    | (@c5 [c]* @c6)
    | (@d5 [d]* @d6)
    )
    ( (@a7 [a]* @a8)
    | (@b7 [b]* @b8)
    | (@c7 [c]* @c8)
    | (@d7 [d]* @d8)
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
        if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
        else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
        else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
        else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
        if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
        else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
        else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
        else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
        outc(out, '\n');
        goto loop;
    }
*/
}
