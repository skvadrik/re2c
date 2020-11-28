/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char *p1, *p2, *p3, *p4;

loop:
    in->tok = in->cur;
/*!use:re2c
    oct  = [0-9]{1,3};
    dot  = [.];
    ipv4 = @p1 oct dot @p2 oct dot @p3 oct dot @p4 oct [\n];

    *    { return 1; }
    ipv4 {
        outs(out, p1, p2 - 1);
        outc(out, ',');
        outs(out, p2, p3 - 1);
        outc(out, ',');
        outs(out, p3, p4 - 1);
        outc(out, ',');
        outs(out, p4, in->cur - 1);
        outc(out, '\n');
        goto loop;
    }
*/
}
