/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
        *a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2,
        *a3, *b3, *c3, *d3, *e3, *f3, *g3, *h3,
        *a4, *b4, *c4, *d4, *e4, *f4, *g4, *h4;
loop:
    in->tok = in->cur;
/*!use:re2c
    * { return 1; }

    ( (@a1 [a]* @a2)
    | (@b1 [b]* @b2)
    | (@c1 [c]* @c2)
    | (@d1 [d]* @d2)
    | (@e1 [e]* @e2)
    | (@f1 [f]* @f2)
    | (@g1 [g]* @g2)
    | (@h1 [h]* @h2)
    )
    ( (@a3 [a]* @a4)
    | (@b3 [b]* @b4)
    | (@c3 [c]* @c4)
    | (@d3 [d]* @d4)
    | (@e3 [e]* @e4)
    | (@f3 [f]* @f4)
    | (@g3 [g]* @g4)
    | (@h3 [h]* @h4)
    )
    [\n] {
        if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
        else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
        else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
        else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
        else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
        else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
        else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
        else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
        if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
        else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
        else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
        else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
        else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
        else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
        else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
        else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
        outc(out, '\n');
        goto loop;
    }
*/
}
