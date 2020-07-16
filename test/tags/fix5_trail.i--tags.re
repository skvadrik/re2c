// re2c $INPUT -o $OUTPUT -i --tags
#include <stddef.h>
#include <stdio.h>

static void lex(const char *YYCURSOR)
{
    const char *YYMARKER, *p0, *p1, *p2, *p3;
    /*!stags:re2c format = "const char *@@;"; */
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        * { printf("error\n"); return; }
        @p0 "0"*
        @p1 "1"
        @p2 "2"*
        @p3 "3"
        / "4"* {
            printf("'%.*s', '%.*s', '%.*s', '%.*s', '%s'\n",
                p1 - p0, p0,
                p2 - p1, p1,
                p3 - p2, p2,
                YYCURSOR - p3, p3,
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
