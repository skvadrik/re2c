#include <stddef.h>
#include <stdio.h>

static void lex(const char *s)
{
#define YYPEEK()           *s
#define YYSKIP()           ++s
#define YYBACKUP()         marker = s
#define YYRESTORE()        s = marker
#define YYBACKUPCTX()      base = s
#define YYRESTORECTX(dist) s = base + dist
#define YYTAG(tag, dist)   tag = base + dist
#define YYDIST()           (s - base)
    const char *marker, *base, *p1, *p2, *p3;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        * { printf("error\n"); return; }
        "0" @p1 "11"
            @p2 "222"
            @p3 "3333"
            / "44444" {
            printf("'%.*s', '%.*s', '%.*s', '%.*s', '%s'\n",
                p1 - base, base,
                p2 - p1, p1,
                p3 - p2, p2,
                s - p3, p3,
                s);
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
