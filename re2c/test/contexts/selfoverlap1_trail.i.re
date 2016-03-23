#include <stddef.h>
#include <stdio.h>

static void lex(const char *YYCURSOR)
{
    const char *YYCTXMARKER;
    const char *token = YYCURSOR;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        * { printf("error\n"); return; }
        "a"+ / "a"+ {
            printf("'%.*s', '%s'\n",
                YYCURSOR - token, token,
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
