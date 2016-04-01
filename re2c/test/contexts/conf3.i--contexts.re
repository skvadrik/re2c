#include <stddef.h>
#include <stdio.h>

static inline unsigned parse_oct(const char *s, const char *e)
{
    unsigned oct = 0;
    for (; s != e; ++s) {
        oct = oct * 10 + *s - '0';
    }
    return oct;
}

static void lex(const char *YYCURSOR)
{
    const char *YYMARKER;
    const char *YYCTXMARKER;
    /*!contexts:re2c sep="\n"; line="long @@ = 0;"; line=; sep=; */
    ptrdiff_t /*!contexts:re2c sep=", "; line="@@ = 0"; */;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:contexts:prefix = "zz_";

        oct = [0-9]{1,3};
        d   = ".";

        * { printf("error\n"); return; }

          oct @p1
        d oct @p2
        d oct @p3
        d oct {
            printf("%u.%u.%u.%u\n",
                parse_oct(YYCTXMARKER, @p1),
                parse_oct(@p1 + 1, @p2),
                parse_oct(@p2 + 1, @p3),
                parse_oct(@p3 + 1, YYCURSOR));
            return;
        }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        lex(argv[i]);
    }
    return 0;
}
