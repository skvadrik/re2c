#include <limits.h>
#include <stdio.h>

template<int base>
static bool adddgt(unsigned long &u, unsigned int d)
{
    if (u > (ULONG_MAX - d) / base) {
        return false;
    }
    u = u * base + d;
    return true;
}

/*!types:re2c*/

static bool lex(const char *s, unsigned long &u)
{
    const char *YYMARKER;
    const char *YYCTXMARKER;
    int c = yycinit;
    u = 0;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = s;
        re2c:define:YYGETCONDITION = "c";
        re2c:define:YYGETCONDITION:naked = 1;
        re2c:define:YYSETCONDITION = "c = @@;";
        re2c:define:YYSETCONDITION:naked = 1;

        <*> * { return false; }

        <init> '0b' / [01]        :=> bin
        <init> "0"                :=> oct
        <init> "" / [1-9]         :=> dec
        <init> '0x' / [0-9a-fA-F] :=> hex

        <bin, oct, dec, hex> "\x00" { return true; }
        <bin> [01]  { if (!adddgt<2>(u, s[-1] - '0')) return false; goto yyc_bin; }
        <oct> [0-7] { if (!adddgt<8>(u, s[-1] - '0')) return false; goto yyc_oct; }
        <dec> [0-9] { if (!adddgt<10>(u, s[-1] - '0')) return false; goto yyc_dec; }
        <hex> [0-9] { if (!adddgt<16>(u, s[-1] - '0'))      return false; goto yyc_hex; }
        <hex> [a-f] { if (!adddgt<16>(u, s[-1] - 'a' + 10)) return false; goto yyc_hex; }
        <hex> [A-F] { if (!adddgt<16>(u, s[-1] - 'A' + 10)) return false; goto yyc_hex; }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        unsigned long u;
        if (lex(argv[i], u)) {
            printf("%lu\n", u);
        } else {
            printf("error\n");
        }
    }
    return 0;
}
