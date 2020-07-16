// re2c $INPUT -o $OUTPUT -i
/*

assuming filename a.re:

$ re2c -i a.re -oa.cc -W && g++ a.cc -oa -Wall -Wextra && ./a
z: 7a
ы: d1 8b
(nil): 00
й: d0 b9
1: 31
lex error: c0 61 ff 61
skipping one byte ...
a: 61
lex error: ff 61
skipping one byte ...
a: 61
done!

z: 7a
ы: d1 8b
(nil): 00
й: d0 b9
1: 31
lex error: c0 61 ff 61 ff ff ff ff
skipping one byte ...
a: 61
lex error: ff 61 ff ff ff ff
skipping one byte ...
a: 61
done!

z: 7a
ы: d1 8b
(nil): 00
й: d0 b9
1: 31
lex error: c0 61 ff 61
skipping one byte ...
a: 61
lex error: ff 61
skipping one byte ...
a: 61
done!

*/

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/*!re2c
    re2c:define:YYCTYPE = uint8_t;
    re2c:define:YYCURSOR = cur;
    re2c:define:YYLIMIT = end;
    re2c:flags:utf-8 = 1;
*/

enum Ecode {EOK, EEOF, ENOLEX};

struct Result {
    Ecode err;
    uint8_t *pos;
};

static void print_bytes(const uint8_t *s, const uint8_t *e)
{
    for (; s < e; ++s) printf(" %02x", *s);
    printf("\n");
}

typedef Result (lex1_t)(uint8_t*, uint8_t*, uint8_t*);

static Result lex1_sentinel(uint8_t *cur, uint8_t *end, uint8_t* /* unused */)
{
    uint8_t *YYMARKER, *tok = cur;
    /*!re2c
        re2c:yyfill:enable = 0;

        . { return {EOK, cur}; }
        * { return {tok == end && *tok == 0xc0 ? EEOF : ENOLEX, tok}; }
    */
}

/*!max:re2c*/

static Result lex1_default(uint8_t *cur, uint8_t *end, uint8_t *last)
{
    uint8_t *YYMARKER, *tok = cur;
    /*!re2c
        re2c:yyfill:enable = 1;
        re2c:define:YYFILL:naked = 1;
        re2c:define:YYFILL = 'assert(false);';

        . { return {EOK, cur}; }
        * { return {tok == last ? EEOF : ENOLEX, tok}; }
    */
}

static int fill() { return 1; } // always error

static Result lex1_simple(uint8_t *cur, uint8_t* end, uint8_t* /* unused */)
{
    uint8_t *YYMARKER, *tok = cur;
    /*!re2c
        re2c:yyfill:enable = 1;
        re2c:define:YYFILL:naked = 0;
        re2c:define:YYFILL = fill;
        re2c:eof = 0;

        . { return {EOK, cur}; }
        $ { return {EEOF, cur}; }
        * { return {ENOLEX, tok}; }
    */
}

static void lex(uint8_t *cur, uint8_t *end, uint8_t *lim, lex1_t *f)
{
    Result res;
    for (;;) {
        res = f(cur, end, lim);
        if (res.err == EEOF) {
            printf("done!\n\n");
            break;
        }
        else if (res.err == ENOLEX) {
            printf("lex error:");
            print_bytes(res.pos, end);
            printf("skipping one byte ...\n");
            cur = res.pos + 1;
        }
        else {
            assert (res.err == EOK);
            if (*cur) printf("%.*s:", (int)(res.pos - cur), cur);
            else printf("(nil):");
            print_bytes(cur, res.pos);
            cur = res.pos;
        }
    }
}

static void lex_sentinel(char *str, size_t len)
{
    str[len] = 0xc0;
    uint8_t *cur = (uint8_t*)str, *end = cur + len;
    lex(cur, end, NULL, lex1_sentinel);
    str[len] = 0;
}

static void lex_default(char *str, size_t len)
{
    uint8_t *buf = new uint8_t[len + YYMAXFILL];
    uint8_t *cur = buf;
    uint8_t *end = buf + len;
    uint8_t *lim = end + YYMAXFILL;
    memcpy(buf, str, len);
    memset(end, 0xff, YYMAXFILL);
    lex(cur, lim, end, lex1_default);
    delete[] buf;
}

static void lex_simple(char *str, size_t len)
{
    uint8_t *cur = (uint8_t*)str, *end = cur + len;
    lex(cur, end, NULL, lex1_simple);
}

int main()
{
    char s[] = "zы\x00й1aaaa";
    const size_t l = sizeof(s) - 1;
    s[l - 4] = 0xc0;
    s[l - 2] = 0xff;

    lex_sentinel(s, l);
    lex_default(s, l);
    lex_simple(s, l);

    return 0;
}
