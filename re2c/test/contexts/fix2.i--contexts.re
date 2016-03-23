#include <stddef.h>
#include <stdio.h>

static void lex(const char *YYCURSOR)
{
#define YYDISTTYPE ptrdiff_t
    const char *YYMARKER;
    const char *YYCTXMARKER;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        * { printf("error\n"); return; }
        "0" @p1 "11"
            @p2 "222"
            @p3 "3333"
            @p4 "44444" {
            printf("'%.*s', '%.*s', '%.*s', '%.*s', '%.*s'\n",
                @p1 - YYCTXMARKER, YYCTXMARKER,
                @p2 - @p1, @p1,
                @p3 - @p2, @p2,
                @p4 - @p3, @p3,
                YYCURSOR - @p4, @p4);
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
