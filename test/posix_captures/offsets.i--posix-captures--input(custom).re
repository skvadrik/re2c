// re2c $INPUT -o $OUTPUT -i --posix-captures --input custom
#include <stddef.h>
#include <stdio.h>

static void lex(const char *s)
{
#define YYPEEK()           *s
#define YYSKIP()           ++s
#define YYBACKUP()         marker = s
#define YYRESTORE()        s = marker
#define YYSTAGP(t)         t = (s - p)
#define YYSTAGN(t)         t = 0
    /*!maxnmatch:re2c*/
    size_t yynmatch;
    const char *marker, *p = s;
    long yypmatch[YYMAXNMATCH * 2];
    /*!stags:re2c format = "long @@;"; */
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        * { printf("error\n"); return; }
        ("a" | "aa")* {
            printf("'%.*s', '%.*s'\n",
                yypmatch[1] - yypmatch[0], p + yypmatch[0],
                yypmatch[3] - yypmatch[2], p + yypmatch[2]);
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
