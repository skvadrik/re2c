// re2c $INPUT -o $OUTPUT -i --recursive-functions --arch x86 --vectorize-loops
#include <assert.h>
#include <immintrin.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    const char *str;
    const char *cur;
    const char *lim;
    const char *mar;
} Input;

/*!re2c
    re2c:api:style = free-form;
    re2c:define:YYFN     = ["lex_rec;static int", "in;Input*"];
    re2c:define:YYCTYPE  = "unsigned char";
    re2c:define:YYCURSOR = "in->cur";
    re2c:define:YYLIMIT  = "in->lim";
    re2c:define:YYMARKER = "in->mar";
    re2c:define:YYFILL   = "return -2;";

    [a-zA-Z_][a-zA-Z0-9_]* { return (int)(in->cur - in->str); }
    *                      { return -1; }
*/

int main(void) {
    char buf[256];
    memset(buf, 'z', 110);
    buf[110] = '!';
    memset(buf + 111, 0, sizeof(buf) - 111);

    Input in = {buf, buf, buf + sizeof(buf), buf};
    assert(lex_rec(&in) == 110);
    return 0;
}
