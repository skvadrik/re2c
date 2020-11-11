/*!include:re2c "common.re" */
/*!include:re2c "fill_email.re" */

static int lex(input_t *in, Output *out)
{
    const char *p;

loop:
    in->tok = in->cur;

/*!use:re2c
    char      = [a-z0-9!#$%&'*+/=?^_`{|}~-];
    before_at = char+ ([.] char+)*;
    az09      = [a-z0-9];
    az09dash  = [a-z0-9-]* [a-z0-9];
    after_at  = (az09 az09dash? [.])+ az09 az09dash?;
    email     = before_at [@] @p after_at [\n];
    skip      = [^\n]* [\n];

    * { return 1; }
    email {
        outc(out, ' ');
        outs(out, in->tok, p - 1);
        outc(out, ' ');
        outs(out, p, in->cur - 1);
        outc(out, '\n');
        goto loop;
    }
    skip { goto loop; }
*/
}
