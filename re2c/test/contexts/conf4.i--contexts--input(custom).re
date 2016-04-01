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

struct contexts_t
{
    /*!contexts:re2c line="long @@;"; */

    contexts_t(): /*!contexts:re2c line="@@(0)"; sep=","; */ {}
    void push(/*!contexts:re2c line="long arg_@@"; sep=","; */)
    {
        /*!contexts:re2c line="@@ = arg_@@;"; */
    }
    void pop(/*!contexts:re2c line="long &arg_@@"; sep=","; */)
    {
        /*!contexts:re2c line="arg_@@ = @@;"; */
    }
};

static void lex(const char *s)
{
#define YYPEEK()           *s
#define YYSKIP()           ++s
#define YYBACKUP()         marker = s
#define YYRESTORE()        s = marker
#define YYBACKUPCTX()      basectx = s
#define YYRESTORECTX(dist) s = basectx + dist
#define ZZ_CTX(dist)       (basectx + dist)
#define ZZ_DIST()          (s - basectx)
    const char *marker;
    const char *basectx;
    contexts_t ctxs;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        re2c:define:YYCTX = "ZZ_CTX";
        re2c:define:YYDIST = "ZZ_DIST";
        re2c:contexts:prefix = "zz_";
        re2c:contexts:expr = "ctxs.@@";

        oct = [0-9]{1,3};
        d   = ".";

        * { printf("error\n"); return; }

          oct @p1
        d oct @p2
        d oct @p3
        d oct {
            printf("%u.%u.%u.%u\n",
                parse_oct(basectx, @p1),
                parse_oct(@p1 + 1, @p2),
                parse_oct(@p2 + 1, @p3),
                parse_oct(@p3 + 1, s));
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
