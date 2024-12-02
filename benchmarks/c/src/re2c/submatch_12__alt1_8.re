/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
        *a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2;
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
    [\n] {
        if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
        else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
        else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
        else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
        else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
        else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
        else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
        else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
        outc(out, '\n');
        goto loop;
    }
*/
}
