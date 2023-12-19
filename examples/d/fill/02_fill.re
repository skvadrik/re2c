// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.string;
import core.stdc.stdio;

/*!max:re2c*/
enum BUFSIZE = (4096 - YYMAXFILL);

struct Input {
    FILE* file;
    char[BUFSIZE + YYMAXFILL] buf;
    char* lim, cur, tok;
    bool eof;
};

private int fill(ref Input input, size_t need) {
    if (input.eof) return 1;

    const size_t shift = input.tok - input.buf.ptr;
    const size_t used = input.lim - input.tok;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < need) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(input.buf.ptr, input.tok, used);
    input.lim -= shift;
    input.cur -= shift;
    input.tok -= shift;

    // Fill free space at the end of buffer with new data from file.
    input.lim += fread(input.lim, 1, BUFSIZE - used, input.file);

    // If read less than expected, this is end of input => add zero padding
    // so that the lexer can access characters at the end of buffer.
    if (input.lim < input.buf.ptr + BUFSIZE) {
        input.eof = true;
        memset(input.lim, 0, YYMAXFILL);
        input.lim += YYMAXFILL;
    }

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
        re2c:define:YYFILL     = "if (fill(input, @@) != 0) return -1;";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return input.tok == input.lim - YYMAXFILL ? count : -1;
        }
        str  { ++count; continue; }
        [ ]+ { continue; }
        *    { return -1; }
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
        fwrite(content.ptr, 1, content.length - 1, f);
    }
    fclose(f);
    int count = 3 * BUFSIZE; // number of quoted strings written to file

    // Initialize lexer state: all pointers are at the end of buffer.
    // This immediately triggers YYFILL, as the check `in.cur < in.lim` fails.
    Input input;
    input.file = fopen(fname.ptr, "r");
    input.cur = input.tok = input.lim = input.buf.ptr + BUFSIZE;
    input.eof = 0;

    // Run the lexer.
    assert(lex(input) == count);

    // Cleanup: remove input file.
    fclose(input.file);
    remove(fname.ptr);
}
