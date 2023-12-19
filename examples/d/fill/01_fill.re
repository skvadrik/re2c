// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.string;
import core.stdc.stdio;

enum BUFSIZE = 4095;

struct Input {
    FILE* file;
    char[BUFSIZE + 1] buf;// +1 for sentinputel
    char* lim, cur, mar, tok;
    bool eof;
};

private int fill(ref Input input) {
    if (input.eof) return 1;

    const size_t shift = input.tok - input.buf.ptr;
    const size_t used = input.lim - input.tok;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < 1) return 2;

    // Shift buffer contents (discard everythinputg up to the current token).
    memmove(cast(void*)input.buf.ptr, input.tok, used);
    input.lim -= shift;
    input.cur -= shift;
    input.mar -= shift;
    input.tok -= shift;

    // Fill free space at the end of buffer with new data from file.
    input.lim += fread(input.lim, 1, BUFSIZE - used, input.file);
    input.lim[0] = 0;
    input.eof = input.lim < (input.buf.ptr + BUFSIZE);
    return 0;
}

private int lex(ref Input input) {
    int count = 0;
    for (;;) {
        input.tok = input.cur;
    /*!re2c
        re2c:define:YYCTYPE    = "char";
        re2c:define:YYSKIP     = "input.cur++;";
        re2c:define:YYPEEK     = "(*input.cur)";
        re2c:define:YYBACKUP   = "input.mar = input.cur;";
        re2c:define:YYRESTORE  = "input.cur = input.mar;";
        re2c:define:YYLESSTHAN = "input.lim <= input.cur";
        re2c:define:YYFILL     = "fill(input) == 0";
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

    // Prepare inputput file: a few times the size of the buffer, containing
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
    input.cur = input.mar = input.tok = input.lim = input.buf.ptr + BUFSIZE;
    input.eof = 0;
    // Sentinel (at YYLIMIT pointer) is set to zero, which triggers YYFILL.
    input.lim[0] = 0;

    // Run the lexer.
    assert(lex(input) == count);

    // Cleanup: remove input file.
    fclose(input.file);
    remove(fname.ptr);
}
