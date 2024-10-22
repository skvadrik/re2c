// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.string;
import core.stdc.stdio;

enum BUFSIZE = 4095;

struct Input {
    FILE* file;
    char[BUFSIZE + 1] buffer;// +1 for sentinel
    char* yylimit, yycursor, yymarker, token;
    bool eof;
};

private int fill(ref Input it) {
    if (it.eof) return 1;

    const size_t shift = it.token - it.buffer.ptr;
    const size_t used = it.yylimit - it.token;

    // Error: lexeme too long. In real life could reallocate a larger buffer.
    if (shift < 1) return 2;

    // Shift buffer contents (discard everything up to the current token).
    memmove(cast(void*)it.buffer.ptr, it.token, used);
    it.yylimit -= shift;
    it.yycursor -= shift;
    it.yymarker -= shift;
    it.token -= shift;

    // Fill free space at the end of buffer with new data from file.
    it.yylimit += fread(it.yylimit, 1, BUFSIZE - used, it.file);
    it.yylimit[0] = 0;
    it.eof = it.yylimit < (it.buffer.ptr + BUFSIZE);
    return 0;
}

private int lex(ref Input yyrecord) {
    int count = 0;
    for (;;) {
        yyrecord.token = yyrecord.yycursor;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = "char";
        re2c:YYFILL = "fill(yyrecord) == 0";
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
    Input it;
    it.file = fopen(fname.ptr, "r");
    it.yycursor = it.yymarker = it.token = it.yylimit = it.buffer.ptr + BUFSIZE;
    it.eof = 0;
    // Sentinel (at YYLIMIT pointer) is set to zero, which triggers YYFILL.
    it.yylimit[0] = 0;

    // Run the lexer.
    assert(lex(it) == count);

    // Cleanup: remove input file.
    fclose(it.file);
    remove(fname.ptr);
}
