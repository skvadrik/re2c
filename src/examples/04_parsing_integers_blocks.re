#include <stdio.h>

static int lex(const char *s)
{
    const char *YYMARKER;
    const char *YYCTXMARKER;
    int n = 0;

    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = s;

        end = "\x00";
    */

    /*!re2c
        *                  { return -1; }
        '0b' / [01]        { goto bin; }
        "0"                { goto oct; }
        "" / [1-9]         { goto dec; }
        '0x' / [0-9a-fA-F] { goto hex; }
    */

bin:
    /*!re2c
        *     { return -1; }
        end   { return n; }
        [01]  { n = (n << 1) + (s[-1] - '0'); goto bin; }
    */

oct:
    /*!re2c
        *     { return -1; }
        end   { return n; }
        [0-7] { n = (n << 3) + (s[-1] - '0'); goto oct; }
    */

dec:
    /*!re2c
        *     { return -1; }
        end   { return n; }
        [0-9] { n = (n * 10) + (s[-1] - '0'); goto dec; }
    */

hex:
    /*!re2c
        *     { return -1; }
        end   { return n; }
        [0-9] { n = (n << 4) + (s[-1] - '0');      goto hex; }
        [a-f] { n = (n << 4) + (s[-1] - 'a' + 10); goto hex; }
        [A-F] { n = (n << 4) + (s[-1] - 'A' + 10); goto hex; }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        const int n = lex(argv[i]);
        if (n < 0) {
            printf("error :[\n");
        } else {
            printf("%d\n", n);
        }
    }
    return 0;
}
