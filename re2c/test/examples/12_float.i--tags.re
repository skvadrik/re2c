#include <math.h>
#include <stdio.h>

static double lex(const char *YYCURSOR)
{
    const char *YYMARKER, *h1, *h2, *l1, *l2, *e1, *e2, *n;
    long e = 0;
    double d = 0;
    /*!stags:re2c format = 'const char *@@;'; */
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        end  = [\x00];
        dot  = ".";
        high = @h1 [0-9]* @h2;
        low  = @l1 [0-9]* @l2;
        exp  = 'e' ([+]? | @n [-]) @e1 [0-9]+ @e2;

        *               { return NAN; }
        (exp | dot) end { return NAN; }

        high (dot low)? exp? end {
            for (; e1 < e2; ++e1) e = e * 10 + *e1 - '0';
            e = (n ? -e : e) - (l2 - l1);
            for (; h1 < h2; ++h1) d = d * 10 + *h1 - '0';
            for (; l1 < l2; ++l1) d = d * 10 + *l1 - '0';
            for (; e < 0; ++e) d /= 10;
            for (; e > 0; --e) d *= 10;
            return d;
        }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        printf("%g\n", lex(argv[i]));
    }
    return 0;
}
