// re2c $INPUT -o $OUTPUT -i --vectorize-loops --api generic
// Loops must not be vectorized with the generic API: the vector loop would
// access input through YYCURSOR directly, bypassing YYPEEK and YYSKIP (here
// the cursor is an index, not a pointer).
#include <assert.h>
#include <string.h>

/*!max:re2c*/

static int lex(const char *str, unsigned int len) {
    unsigned int cur = 0, lim = len + YYMAXFILL;
    char buf[256];
    assert(len + YYMAXFILL <= sizeof(buf));
    memcpy(buf, str, len);
    memset(buf + len, 0, YYMAXFILL);
    int count = 0;

loop:
    /*!re2c
        re2c:api:style = free-form;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "buf[cur]";
        re2c:YYSKIP = "++cur;";
        re2c:YYLESSTHAN = "lim - cur < @@";
        re2c:YYFILL = "return -1;";

        [\x00]  { return cur - 1 == len ? count : -1; }
        [a-z]+  { ++count; goto loop; }
        [ ]+    { goto loop; }
        *       { return -1; }
    */
}

#define TEST(s, r) assert(lex(s, sizeof(s) - 1) == r)
int main() {
    TEST("", 0);
    TEST("abc def", 2);
    TEST("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz abcdefghijklmnopqrstuvwxyz", 2);
    TEST("abc 1", -1);
    return 0;
}
