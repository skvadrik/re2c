// re2c $INPUT -o $OUTPUT
#include <assert.h>

// Expect a null-terminated string.
static int lex(const char *YYCURSOR) {
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        *      { return -1; }
        [\x00] { return count; }
        [a-z]+ { ++count; continue; }
        [ ]+   { continue; }
    */
    }
}

int main() {
    assert(lex("") == 0);
    assert(lex("one two three") == 3);
    assert(lex("f0ur") == -1);
    return 0;
}
