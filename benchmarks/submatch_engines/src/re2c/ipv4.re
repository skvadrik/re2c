/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char *p1, *p2, *p3, *p4;

loop:
    in->tok = in->cur;
/*!re2c
    end  = "\x00";
    oct  = [0-9]{1,3};
    dot  = [.];
    nl   = [\n];
    ipv4 = @p1 oct dot @p2 oct dot @p3 oct dot @p4 oct nl;

    *    { return 1; }
    end  { return 0; }
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
