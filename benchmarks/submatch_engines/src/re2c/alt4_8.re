/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
        *a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2,
        *a3, *b3, *c3, *d3, *e3, *f3, *g3, *h3,
        *a4, *b4, *c4, *d4, *e4, *f4, *g4, *h4,
        *a5, *b5, *c5, *d5, *e5, *f5, *g5, *h5,
        *a6, *b6, *c6, *d6, *e6, *f6, *g6, *h6,
        *a7, *b7, *c7, *d7, *e7, *f7, *g7, *h7,
        *a8, *b8, *c8, *d8, *e8, *f8, *g8, *h8;
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
    ( (@a5 [a]* @a6)
    | (@b5 [b]* @b6)
    | (@c5 [c]* @c6)
    | (@d5 [d]* @d6)
    | (@e5 [e]* @e6)
    | (@f5 [f]* @f6)
    | (@g5 [g]* @g6)
    | (@h5 [h]* @h6)
    )
    ( (@a7 [a]* @a8)
    | (@b7 [b]* @b8)
    | (@c7 [c]* @c8)
    | (@d7 [d]* @d8)
    | (@e7 [e]* @e8)
    | (@f7 [f]* @f8)
    | (@g7 [g]* @g8)
    | (@h7 [h]* @h8)
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
        if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
        else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
        else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
        else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
        else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
        else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
        else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
        else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
        if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
        else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
        else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
        else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
        else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
        else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
        else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
        else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
        outc(out, '\n');
        goto loop;
    }
*/
}
