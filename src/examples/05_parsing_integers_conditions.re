#include <stdio.h>

/*!types:re2c*/

static int lex(const char *s)
{
    const char *YYMARKER;
    const char *YYCTXMARKER;
    int n = 0;
    int c = yycinit;

    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = s;
        re2c:define:YYGETCONDITION = "c";
        re2c:define:YYGETCONDITION:naked = 1;
        re2c:define:YYSETCONDITION = "c = @@;";
        re2c:define:YYSETCONDITION:naked = 1;

        <*> * { return -1; }

        <init> '0b' / [01]        :=> bin
        <init> "0"                :=> oct
        <init> "" / [1-9]         :=> dec
        <init> '0x' / [0-9a-fA-F] :=> hex

        <bin, oct, dec, hex> "\x00" { return n; }
        <bin> [01]  { n = (n << 1) + (s[-1] - '0'); goto yyc_bin; }
        <oct> [0-7] { n = (n << 3) + (s[-1] - '0'); goto yyc_oct; }
        <dec> [0-9] { n = (n * 10) + (s[-1] - '0'); goto yyc_dec; }
        <hex> [0-9] { n = (n << 4) + (s[-1] - '0');      goto yyc_hex; }
        <hex> [a-f] { n = (n << 4) + (s[-1] - 'a' + 10); goto yyc_hex; }
        <hex> [A-F] { n = (n << 4) + (s[-1] - 'A' + 10); goto yyc_hex; }
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
