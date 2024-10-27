// re2c $INPUT -o $OUTPUT
#include <cassert>
#include <cstdio>
#include <fstream>
#include <sstream>

static void convert_newlines(std::ifstream &in, std::ostringstream &out) {
    std::streampos mar;
    for (;;) {
    /*!re2c
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:YYCTYPE = char;
        re2c:YYPEEK = "in.peek()";
        re2c:YYSKIP = "{ in.ignore(); if (in.eof()) return; }";
        re2c:YYBACKUP = "mar = in.tellg();";
        re2c:YYRESTORE = "in.seekg(mar);";
        re2c:yyfill:enable = 0;

        *      { out.put(yych); continue; }
        "\r\n" { out.put('\n'); continue; }
    */
    }
}

int main() {
    const char *fname = "input";
    const char s1[] = "Text\r\nwith\r\nnewlines.\r\n\r\n";
    const char s2[] = "Text\nwith\nnewlines.\n\n";

    std::ofstream f(fname, std::ios::binary);
    f.write(s1, sizeof(s1) - 1);
    f.close();

    std::ifstream in(fname, std::ios::binary);
    std::ostringstream out;
    convert_newlines(in, out);
    assert(out.str() == s2);

    remove(fname);
    return 0;
}
