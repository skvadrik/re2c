// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 4095

struct Input {
    FILE *file;
    char buffer[BUFSIZE + 1]; // +1 for sentinel
    char *yylimit;
    char *yycursor;
    char *yymarker;
    char *token;
    bool eof;
};

static int fill(Input &in) {
    if (in.eof) return 1;

    const size_t shift = in.token - in.buffer;
    const size_t used = in.yylimit - in.token;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < 1) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(in.buffer, in.token, used);
    in.yylimit -= shift;
    in.yycursor -= shift;
    in.yymarker -= shift;
    in.token -= shift;

    // Fill free space at the end of buffer with new data from file.
    in.yylimit += fread(in.yylimit, 1, BUFSIZE - used, in.file);
    in.yylimit[0] = 0;
    in.eof = in.yylimit < in.buffer + BUFSIZE;
    return 0;
}

static int lex(Input *yyrecord) {
    int count = 0;
loop:
    yyrecord->token = yyrecord->yycursor;
    /*!re2c
        re2c:api = record;
        re2c:define:YYCTYPE = char;
        re2c:define:YYFILL = "fill(*yyrecord) == 0";
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
    in.yycursor = in.yymarker = in.token = in.yylimit = in.buffer + BUFSIZE;
    in.eof = 0;
    // Sentinel (at YYLIMIT pointer) is set to zero, which triggers YYFILL.
    in.yylimit[0] = 0;

    // Run the lexer.
    assert(lex(&in) == count);

    // Cleanup: remove input file.
    fclose(in.file);
    remove(fname);
    return 0;
}
