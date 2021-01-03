/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *s1, *y1, *h1, *m1, *d1, *M1, *z1,
        *s2, *y2, *h2, *m2, *d2, *M2, *z2;
loop:
    in->tok = in->cur;
/*!re2c
    end = "\x00";

    year     = @y1 (([1-9][0-9]*)? [0-9]{4}) @y2;
    month    = @m1 ([1][0-2] | [0][1-9]) @m2;
    day      = @d1 ([3][0-1] | [0][1-9] | [1-2][0-9]) @d2;
    hours    = @h1 ([2][0-3] | [0-1][0-9]) @h2;
    minutes  = @M1 [0-5][0-9] @M2;
    seconds  = @s1 [0-5][0-9] @s2;
    timezone = @z1 ([Z] | [+-]([2][0-3] | [0-1][0-9])[:][0-5][0-9]) @z2;
    date     = year [-] month [-] day [T] hours [:] minutes [:] seconds timezone [\n];

    *    { return 1; }
    end  { return 0; }
    date {
        OUTS("{'year'='");
        outs(out, y1, y2);
        OUTS("', 'month'='");
        outs(out, m1, m2);
        OUTS("', 'day'='");
        outs(out, d1, d2);
        OUTS("', 'hours'='");
        outs(out, h1, h2);
        OUTS("', 'minutes'='");
        outs(out, M1, M2);
        OUTS("', 'seconds'='");
        outs(out, s1, s2);
        OUTS("', 'tz'='");
        outs(out, z1, z2);
        OUTS("'}\n");
        goto loop;
    }
*/
}
