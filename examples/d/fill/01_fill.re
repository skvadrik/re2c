// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.string;
import core.stdc.stdio;

enum BUFSIZE = 4095;

struct Input {
    FILE* file;
    char[BUFSIZE + 1] str;// +1 for sentinel
    char* lim, cur, mar, tok;
    bool eof;
};

private int fill(ref Input input) {
    if (input.eof) return 1;

    const size_t shift = input.tok - input.str.ptr;
    const size_t used = input.lim - input.tok;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < 1) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(cast(void*)input.str.ptr, input.tok, used);
    input.lim -= shift;
    input.cur -= shift;
    input.mar -= shift;
    input.tok -= shift;

    // Fill free space at the end of buffer with new data from file.
    input.lim += fread(input.lim, 1, BUFSIZE - used, input.file);
    input.lim[0] = 0;
    input.eof = input.lim < (input.str.ptr + BUFSIZE);
    return 0;
}

private int lex(ref Input yyrecord) {
    int count = 0;
    for (;;) {
        yyrecord.tok = yyrecord.cur;
    /*!re2c
        re2c:api = record;
        re2c:define:YYCTYPE = "char";
        re2c:define:YYFILL = "fill(yyrecord) == 0";
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return count; }
        str  { ++count; continue; }
        [ ]+ { continue; }
    */
    }
    assert(0);
}

void main() {
    const char[] fname = "input";
    const char[] content = "'qu\0tes' 'are' 'fine: \\'' ";

    // Prepare input file: a few times the size of the buffer, containing
    // strings with zeroes and escaped quotes.
    FILE* f = fopen(fname.ptr, "w");
    for (int i = 0; i < BUFSIZE; ++i) {
        fwrite(cast(const(void*)) content.ptr, 1, content.length - 1, f);
    }
    fclose(f);
    int count = 3 * BUFSIZE; // number of quoted strings written to file

    // Initialize lexer state: all pointers are at the end of buffer.
    Input input;
    input.file = fopen(fname.ptr, "r");
    input.cur = input.mar = input.tok = input.lim = input.str.ptr + BUFSIZE;
    input.eof = 0;
    // Sentinel (at YYLIMIT pointer) is set to zero, which triggers YYFILL.
    input.lim[0] = 0;

    // Run the lexer.
    assert(lex(input) == count);

    // Cleanup: remove input file.
    fclose(input.file);
    remove(fname.ptr);
}
