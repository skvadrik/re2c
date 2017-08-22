#include <stdio.h>

static int lex(const char *YYCURSOR)
{
    const char *YYMARKER, *o1, *o2, *o3, *o4;
    /*!stags:re2c format = 'const char *@@;'; */
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        end = "\x00";
        oct = [0-9]{1,3};
        dot = ".";

        * { printf("error\n"); return 1; }

        @o1 oct dot @o2 oct dot @o3 oct dot @o4 oct {
            printf("parsed: %.*s, %.*s, %.*s, %*s!\n",
                (int)(o2 - o1 - 1), o1,
                (int)(o3 - o2 - 1), o2,
                (int)(o4 - o3 - 1), o3,
                (int)(YYCURSOR - o4), o4);
            return 0;
        }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) lex(argv[i]);
    return 0;
}
