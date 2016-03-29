#include <stddef.h>
#include <stdio.h>

static void lex(const char *cursor)
{
#   define YYPEEK()           *cursor
#   define YYSKIP()           ++cursor
#   define YYBACKUP()         marker = cursor
#   define YYBACKUPCTX()      ctxmarker = cursor
#   define YYRESTORE()        cursor = marker
#   define YYRESTORECTX(dist) cursor = ctxmarker + dist
#   define ZZZ_DIST()         (cursor - ctxmarker)
#   define ZZZ_CTX(dist)      (ctxmarker + dist)
    const char *marker;
    const char *ctxmarker;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:define:YYCTX = "ZZZ_CTX";
        re2c:define:YYDIST = "ZZZ_DIST";
        re2c:define:YYDISTTYPE = ptrdiff_t;
        re2c:ctxprefix = "zzz_";

        * { printf("error\n"); return; }
        "0"*
            @p1 "1"
            @p2 "2"*
            @p3 "3"
            / "4"* {
            printf("'%.*s', '%.*s', '%.*s', '%.*s', '%s'\n",
                @p1 - ctxmarker, ctxmarker,
                @p2 - @p1, @p1,
                @p3 - @p2, @p2,
                cursor - @p3, @p3,
                cursor);
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
