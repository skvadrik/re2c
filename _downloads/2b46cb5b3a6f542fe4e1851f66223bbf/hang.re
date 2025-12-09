#include <stdio.h>

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        for (char *YYCURSOR = argv[i];;) {
        /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:yyfill:enable = 0;
            "\x00" { break; }
            [a-z]* { continue; }
        */
        }
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}
