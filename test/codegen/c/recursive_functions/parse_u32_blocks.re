// re2c $INPUT -o $OUTPUT -i --recursive-functions
#include <stdint.h>
#include <limits.h>
#include <assert.h>

static const uint64_t ERROR = ~0lu;

struct State
{
    const char* cur;
    const char* mar;
    uint64_t num;
};

template<int BASE> static void adddgt(uint64_t &u, unsigned int d)
{
    u = u * BASE + d;
    if (u > UINT32_MAX) u = ERROR;
}

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = char;
    re2c:define:YYCURSOR = st.cur;
    re2c:define:YYMARKER = st.mar;

    end = "\x00";
*/

/*!local:re2c
    re2c:define:YYFN = ["lex_bin;uint64_t", "st;State&"];

    end   { return st.num; }
    [01]  { adddgt<2>(st.num, st.cur[-1] - '0'); return lex_bin(st); }
    *     { return ERROR; }
*/

/*!local:re2c
    re2c:define:YYFN = ["lex_oct;uint64_t", "st;State&"];

    end   { return st.num; }
    [0-7] { adddgt<8>(st.num, st.cur[-1] - '0'); return lex_oct(st); }
    *     { return ERROR; }
*/

/*!local:re2c
    re2c:define:YYFN = ["lex_dec;uint64_t", "st;State&"];

    end   { return st.num; }
    [0-9] { adddgt<10>(st.num, st.cur[-1] - '0'); return lex_dec(st); }
    *     { return ERROR; }
*/

/*!local:re2c
    re2c:define:YYFN = ["lex_hex;uint64_t", "st;State&"];

    end   { return st.num; }
    [0-9] { adddgt<16>(st.num, st.cur[-1] - '0');      return lex_hex(st); }
    [a-f] { adddgt<16>(st.num, st.cur[-1] - 'a' + 10); return lex_hex(st); }
    [A-F] { adddgt<16>(st.num, st.cur[-1] - 'A' + 10); return lex_hex(st); }
    *     { return ERROR; }
*/

/*!local:re2c
    re2c:define:YYFN = ["lex_main;uint64_t", "st;State&"];

    '0b' / [01]        { return lex_bin(st); }
    "0"                { return lex_oct(st); }
    "" / [1-9]         { return lex_dec(st); }
    '0x' / [0-9a-fA-F] { return lex_hex(st); }
    *                  { return ERROR; }
*/

static uint64_t parse_u32(const char *s)
{
    State st = {s, nullptr, 0};
    return lex_main(st);
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
