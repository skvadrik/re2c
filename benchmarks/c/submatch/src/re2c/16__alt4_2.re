/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a1, *b1,
        *a2, *b2,
        *a3, *b3,
        *a4, *b4,
        *a5, *b5,
        *a6, *b6,
        *a7, *b7,
        *a8, *b8;
loop:
    in->tok = in->cur;
/*!use:re2c
    * { return 1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    )
    ( (@a3 [a]* @a4)
    | (@b3 [b]* @b4)
    )
    ( (@a5 [a]* @a6)
    | (@b5 [b]* @b6)
    )
    ( (@a7 [a]* @a8)
    | (@b7 [b]* @b8)
    )
    [\n] {
        if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
        else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
        if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
        else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
        if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
        else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
        if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
        else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
        outc(out, '\n');
        goto loop;
    }
*/
}
