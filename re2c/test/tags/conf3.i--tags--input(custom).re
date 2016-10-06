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
    /*!tags:re2c format = "long @@;"; */

    contexts_t();
    void push(/*!tags:re2c
        format = "long arg_@@";
        separator = ","; */);
    void pop(/*!tags:re2c
        format = "long &arg_@@";
        separator = ","; */);
};

static void lex(const char *s)
{
#define YYPEEK()           *s
#define YYSKIP()           ++s
#define YYBACKUP()         marker = s
#define YYRESTORE()        s = marker
#define YYBACKUPCTX()      basectx = s
#define YYRESTORECTX(dist) s = basectx + dist
#define ZZ_CTX(tag, dist)  tag = basectx + dist
#define ZZ_DIST()          (s - basectx)
    const char *marker, *basectx, *p1, *p2, *p3;
    contexts_t ctxs;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        re2c:define:YYTAG = "ZZ_CTX";
        re2c:define:YYDIST = "ZZ_DIST";
        re2c:tags:prefix = "zz_";
        re2c:tags:expression = "ctxs.@@";

        oct = [0-9]{1,3};
        d   = ".";

        * { printf("error\n"); return; }

          oct @p1
        d oct @p2
        d oct @p3
        d oct {
            printf("%u.%u.%u.%u\n",
                parse_oct(basectx, p1),
                parse_oct(p1 + 1, p2),
                parse_oct(p2 + 1, p3),
                parse_oct(p3 + 1, s));
            return;
        }
    */
}

contexts_t::contexts_t(): /*!tags:re2c
    format = "@@(0)";
    separator = ",";
*/ {}

void contexts_t::push(/*!tags:re2c
    format = "long arg_@@";
    separator = ","; */)
{
    /*!tags:re2c format = "@@ = arg_@@;"; */
}

void contexts_t::pop(/*!tags:re2c
    format = "long &arg_@@";
    separator = ","; */)
{
    /*!tags:re2c format = "arg_@@ = @@;"; */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        lex(argv[i]);
    }
    return 0;
}
