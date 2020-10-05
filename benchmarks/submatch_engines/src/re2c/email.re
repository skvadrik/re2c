/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char *p;

loop:
    in->tok = in->cur;
/*!re2c
    // don't fail if YYFILL fails (because of the greedy garbage lexeme)
    re2c:define:YYFILL = "if (fill(in, @@) != 0) return 0;";

    estr     = [a-z0-9!#$%&'*+/=?^_`{|}~-];
    beforeAt = estr+ ([.] estr+)*;
    az09     = [a-z0-9];
    az09dash = [a-z0-9-]* [a-z0-9];
    part     = az09 az09dash? [.];
    afterAt  = part+ az09 az09dash?;
    email    = beforeAt [@] @p afterAt [\n];
    fb       = [^\n]* [\n];

    * { return 1; }
    email {
        outc(out, ' ');
        outs(out, in->tok, p - 1);
        outc(out, ' ');
        outs(out, p, in->cur - 1);
        outc(out, '\n');
        goto loop;
    }
    fb { goto loop; }
*/
}
