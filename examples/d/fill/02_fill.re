// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.string;
import core.stdc.stdio;

/*!max:re2c*/
enum BufSize = (4096 - YYMaxFill);

struct Input {
    FILE* file;
    char[BufSize + YYMaxFill] buffer;
    char* yylimit, yycursor, token;
    bool eof;
};

private int fill(ref Input it, size_t need) {
    if (it.eof) return 1;

    const size_t shift = it.token - it.buffer.ptr;
    const size_t used = it.yylimit - it.token;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < need) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(it.buffer.ptr, it.token, used);
    it.yylimit -= shift;
    it.yycursor -= shift;
    it.token -= shift;

    // Fill free space at the end of buffer with new data from file.
    it.yylimit += fread(it.yylimit, 1, BufSize - used, it.file);

    // If read less than expected, this is end of input => add zero padding
    // so that the lexer can access characters at the end of buffer.
    if (it.yylimit < it.buffer.ptr + BufSize) {
        it.eof = true;
        memset(it.yylimit, 0, YYMaxFill);
        it.yylimit += YYMaxFill;
    }

    return 0;
}

private int lex(ref Input yyrecord) {
    int count = 0;
    for (;;) {
        yyrecord.token = yyrecord.yycursor;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = "char";
        re2c:YYFILL = "if (fill(yyrecord, @@) != 0) return -1;";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            return yyrecord.token == yyrecord.yylimit - YYMaxFill ? count : -1;
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
    for (int i = 0; i < BufSize; ++i) {
        fwrite(content.ptr, 1, content.length - 1, f);
    }
    fclose(f);
    int count = 3 * BufSize; // number of quoted strings written to file

    // Initialize lexer state: all pointers are at the end of buffer.
    // This immediately triggers YYFILL, as the check `it.yycursor < it.yylimit` fails.
    Input it;
    it.file = fopen(fname.ptr, "r");
    it.yycursor = it.token = it.yylimit = it.buffer.ptr + BufSize;
    it.eof = 0;

    // Run the lexer.
    assert(lex(it) == count);

    // Cleanup: remove input file.
    fclose(it.file);
    remove(fname.ptr);
}
