// re2c $INPUT -o $OUTPUT -ci
#include <stdint.h>
#include <limits.h>
#include <assert.h>

static const uint64_t ERROR = ~0lu;
/*!types:re2c*/

template<int BASE> static void adddgt(uint64_t &u, unsigned int d)
{
    u = u * BASE + d;
    if (u > UINT32_MAX) u = ERROR;
}

static uint64_t parse_u32(const char *s)
{
    const char *YYMARKER;
    int c = yycinit;
    uint64_t u = 0;

    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:api:style = free-form;
    re2c:define:YYCTYPE = char;
    re2c:define:YYCURSOR = s;
    re2c:define:YYGETCONDITION = "c";
    re2c:define:YYSETCONDITION = "c = @@;";

    <*> * { return ERROR; }

    <init> '0b' / [01]        :=> bin
    <init> "0"                :=> oct
    <init> "" / [1-9]         :=> dec
    <init> '0x' / [0-9a-fA-F] :=> hex

    <bin, oct, dec, hex> "\x00" { return u; }

    <bin> [01]  { adddgt<2> (u, s[-1] - '0');      goto yyc_bin; }
    <oct> [0-7] { adddgt<8> (u, s[-1] - '0');      goto yyc_oct; }
    <dec> [0-9] { adddgt<10>(u, s[-1] - '0');      goto yyc_dec; }
    <hex> [0-9] { adddgt<16>(u, s[-1] - '0');      goto yyc_hex; }
    <hex> [a-f] { adddgt<16>(u, s[-1] - 'a' + 10); goto yyc_hex; }
    <hex> [A-F] { adddgt<16>(u, s[-1] - 'A' + 10); goto yyc_hex; }
    */
}

int main()
{
    assert(parse_u32("1234567890") == 1234567890);
    assert(parse_u32("0b1101") == 13);
    assert(parse_u32("0x7Fe") == 2046);
    assert(parse_u32("0644") == 420);
    assert(parse_u32("9999999999") == ERROR);
    assert(parse_u32("") == ERROR);
    return 0;
}
