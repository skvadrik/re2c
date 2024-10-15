// re2c $INPUT -o $OUTPUT
#include <assert.h>

long lex(const char *s) {
    const char *YYCURSOR = s;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        number = [1-9][0-9]*;

        number { long x = 0xa'b'c'd1'2'3'4L; return x; }
        *      { return -1; }
    */
}

int main() {
    assert(lex("1234") == 0xabcd1234L);
    return 0;
}
