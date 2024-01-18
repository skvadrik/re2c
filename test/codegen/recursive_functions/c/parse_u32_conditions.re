// re2c $INPUT -o $OUTPUT -ci --recursive-functions
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

static const uint64_t ERROR = ~0lu;
/*!types:re2c*/

struct State
{
    const char* cur;
    const char* mar;
    YYCONDTYPE cond;
    uint64_t num;
};

template<int BASE> static void adddgt(uint64_t &u, unsigned int d)
{
    u = u * BASE + d;
    if (u > UINT32_MAX) u = ERROR;
}

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:api:style = free-form;
    re2c:define:YYFN = ["lex", "uint64_t", "st", "State&"];
    re2c:define:YYCTYPE = char;
    re2c:define:YYCURSOR = st.cur;
    re2c:define:YYMARKER = st.mar;
    re2c:define:YYGETCONDITION = "st.cond";
    re2c:define:YYSETCONDITION = "st.cond = @@;";

    <*> * { return ERROR; }

    <init> '0b' / [01]        :=> bin
    <init> "0"                :=> oct
    <init> "" / [1-9]         :=> dec
    <init> '0x' / [0-9a-fA-F] :=> hex

    <bin, oct, dec, hex> "\x00" { return st.num; }

    <bin> [01]  { adddgt<2> (st.num, st.cur[-1] - '0'); return yyfnbin(st); } // test direct dispatch to condition
    <oct> [0-7] { adddgt<8> (st.num, st.cur[-1] - '0'); return yyfnoct(st); }
    <dec> [0-9] { adddgt<10>(st.num, st.cur[-1] - '0'); return yyfndec(st); }
    <hex> [0-9] { adddgt<16>(st.num, st.cur[-1] - '0');      return lex(st); } // test dispatch via start function
    <hex> [a-f] { adddgt<16>(st.num, st.cur[-1] - 'a' + 10); return lex(st); }
    <hex> [A-F] { adddgt<16>(st.num, st.cur[-1] - 'A' + 10); return lex(st); }
*/

static uint64_t parse_u32(const char *s)
{
    State st = {s, nullptr, yycinit, 0};
    return lex(st);
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
