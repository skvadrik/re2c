// re2c $INPUT -o $OUTPUT -i
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
    uint64_t u = 0;

    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = char;
    re2c:define:YYCURSOR = s;

    end = "\x00";

    '0b' / [01]        { goto bin; }
    "0"                { goto oct; }
    "" / [1-9]         { goto dec; }
    '0x' / [0-9a-fA-F] { goto hex; }
    *                  { return ERROR; }
    */
bin:
    /*!re2c
    end   { return u; }
    [01]  { adddgt<2>(u, s[-1] - '0'); goto bin; }
    *     { return ERROR; }
    */
oct:
    /*!re2c
    end   { return u; }
    [0-7] { adddgt<8>(u, s[-1] - '0'); goto oct; }
    *     { return ERROR; }
    */
dec:
    /*!re2c
    end   { return u; }
    [0-9] { adddgt<10>(u, s[-1] - '0'); goto dec; }
    *     { return ERROR; }
    */
hex:
    /*!re2c
    end   { return u; }
    [0-9] { adddgt<16>(u, s[-1] - '0');      goto hex; }
    [a-f] { adddgt<16>(u, s[-1] - 'a' + 10); goto hex; }
    [A-F] { adddgt<16>(u, s[-1] - 'A' + 10); goto hex; }
    *     { return ERROR; }
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
