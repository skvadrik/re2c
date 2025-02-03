// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 4095

typedef struct {
    FILE *file;
    char buf[BUFSIZE + 1], *lim, *cur, *mar, *tok; // +1 for sentinel
    int eof;
} Input;

static int fill(Input *in) {
    if (in->eof) return 1;

    const size_t shift = in->tok - in->buf;
    const size_t used = in->lim - in->tok;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < 1) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(in->buf, in->tok, used);
    in->lim -= shift;
    in->cur -= shift;
    in->mar -= shift;
    in->tok -= shift;

    // Fill free space at the end of buffer with new data from file.
    in->lim += fread(in->lim, 1, BUFSIZE - used, in->file);
    in->lim[0] = 0;
    in->eof = in->lim < in->buf + BUFSIZE;
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
        re2c:define:YYMARKER = in->mar;
        re2c:define:YYLIMIT = in->lim;
        re2c:define:YYFILL = "fill(in) == 0";
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return count; }
        str  { ++count; goto loop; }
        [ ]+ { goto loop; }
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
    Input in;
    in.file = fopen(fname, "r");
    in.cur = in.mar = in.tok = in.lim = in.buf + BUFSIZE;
    in.eof = 0;
    // Sentinel (at YYLIMIT pointer) is set to zero, which triggers YYFILL.
    in.lim[0] = 0;

    // Run the lexer.
    assert(lex(&in) == count);

    // Cleanup: remove input file.
    fclose(in.file);
    remove(fname);
    return 0;
}
