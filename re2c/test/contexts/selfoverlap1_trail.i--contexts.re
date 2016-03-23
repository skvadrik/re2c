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
        "" @p0 "a"+ / "a"+ {
            printf("'%.*s', '%s'\n",
                YYCURSOR - @p0, @p0,
                YYCURSOR);
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
