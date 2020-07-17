// re2c $INPUT -o $OUTPUT -i --tags --input custom
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

static void lex(const char *s)
{
#define YYPEEK()     *s
#define YYSKIP()     ++s
#define YYBACKUP()   marker = s
#define YYRESTORE()  s = marker
#define ZZTP(t)      t = s
#define ZZTN(t)      t = NULL
#define ZZRT(t)      s = t
    const char *marker, *p0, *p1, *p2, *p3;
    /*!stags:re2c format = "const char *@@;"; */
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        oct = [0-9]{1,3};
        d   = ".";

        * { printf("error\n"); return; }

        @p0
          oct @p1
        d oct @p2
        d oct @p3
        d oct {
            printf("%u.%u.%u.%u\n",
                parse_oct(p0, p1),
                parse_oct(p1 + 1, p2),
                parse_oct(p2 + 1, p3),
                parse_oct(p3 + 1, s));
            return;
        }

        re2c:define:YYSTAGP = "ZZTP";
        re2c:define:YYSTAGN = "ZZTN";
        re2c:define:YYRESTORETAG = "ZZRT";
        re2c:tags:prefix = "zz_";
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        lex(argv[i]);
    }
    return 0;
}
