// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c*/
#define BUFSIZE (4096 - YYMAXFILL)

typedef struct {
    FILE *file;
    char buf[BUFSIZE + YYMAXFILL], *lim, *cur, *tok;
    int eof;
} Input;

static int fill(Input *in, size_t need) {
    if (in->eof) return 1;

    const size_t shift = in->tok - in->buf;
    const size_t used = in->lim - in->tok;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < need) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(in->buf, in->tok, used);
    in->lim -= shift;
    in->cur -= shift;
    in->tok -= shift;

    // Fill free space at the end of buffer with new data from file.
    in->lim += fread(in->lim, 1, BUFSIZE - used, in->file);

    // If read less than expected, this is end of input => add zero padding
    // so that the lexer can access characters at the end of buffer.
    if (in->lim < in->buf + BUFSIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

static int lex(Input *in) {
    int count = 0;
loop:
        in->tok = in->cur;
    /*!re2c
        re2c:api:style = free-form;
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = in->cur;
        re2c:define:YYLIMIT = in->lim;
        re2c:define:YYFILL = "if (fill(in, @@) != 0) return -1;";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return in->tok == in->lim - YYMAXFILL ? count : -1;
        }
        str  { ++count; goto loop; }
        [ ]+ { goto loop; }
        *    { return -1; }
    */
}

int main() {
    const char *fname = "input";
    const char content[] = "'qu\0tes' 'are' 'fine: \\'' ";

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    FILE *f = fopen(fname, "w");
    for (int i = 0; i < BUFSIZE; ++i) {
        fwrite(content, 1, sizeof(content) - 1, f);
    }
    fclose(f);
    int count = 3 * BUFSIZE; // number of quoted strings written to file

    // Initialize lexer state: all pointers are at the end of buffer.
    // This immediately triggers YYFILL, as the check `in->cur < in->lim` fails.
    Input in;
    in.file = fopen(fname, "r");
    in.cur = in.tok = in.lim = in.buf + BUFSIZE;
    in.eof = 0;

    // Run the lexer.
    assert(lex(&in) == count);

    // Cleanup: remove input file.
    fclose(in.file);
    remove(fname);
    return 0;
}
