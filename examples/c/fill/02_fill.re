// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c*/
#define BUFSIZE (4096 - YYMAXFILL)

struct Input {
    FILE *file;
    char buffer[BUFSIZE + YYMAXFILL];
    char *yylimit;
    char *yycursor;
    char *token;
    bool eof;
};

static int fill(Input &in, size_t need) {
    if (in.eof) return 1;

    const size_t shift = in.token - in.buffer;
    const size_t used = in.yylimit - in.token;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < need) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(in.buffer, in.token, used);
    in.yylimit -= shift;
    in.yycursor -= shift;
    in.token -= shift;

    // Fill free space at the end of buffer with new data from file.
    in.yylimit += fread(in.yylimit, 1, BUFSIZE - used, in.file);

    // If read less than expected, this is end of input => add zero padding
    // so that the lexer can access characters at the end of buffer.
    if (in.yylimit < in.buffer + BUFSIZE) {
        in.eof = true;
        memset(in.yylimit, 0, YYMAXFILL);
        in.yylimit += YYMAXFILL;
    }

    return 0;
}

static int lex(Input *yyrecord) {
    int count = 0;
loop:
    yyrecord->token = yyrecord->yycursor;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = char;
        re2c:YYFILL = "if (fill(*yyrecord, @@) != 0) return -1;";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return yyrecord->token == yyrecord->yylimit - YYMAXFILL ? count : -1;
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
    // This immediately triggers YYFILL, as the check `in.yycursor < in.yylimit` fails.
    Input in;
    in.file = fopen(fname, "r");
    in.yycursor = in.token = in.yylimit = in.buffer + BUFSIZE;
    in.eof = 0;

    // Run the lexer.
    assert(lex(&in) == count);

    // Cleanup: remove input file.
    fclose(in.file);
    remove(fname);
    return 0;
}
