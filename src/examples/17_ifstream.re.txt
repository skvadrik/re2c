#include <fstream>

static void conv(std::ifstream &in, std::ofstream &out)
{
    std::streampos mar;
#   define YYCTYPE     char
#   define YYPEEK()    in.peek()
#   define YYSKIP()    do { in.ignore(); if (in.eof()) return; } while(0)
#   define YYBACKUP()  mar = in.tellg()
#   define YYRESTORE() in.seekg(mar)
loop:
    /*!re2c
        re2c:yyfill:enable = 0;

        *      { out.put(yych); goto loop; }
        "\r\n" { out.put('\n'); goto loop; }
    */
}

int main(int argc, char **argv)
{
    if (argc != 3) return 1;

    std::ifstream in(argv[1], std::ios::binary);
    std::ofstream out(argv[2], std::ios::binary);
    if (in.fail() || out.fail()) return 2;

    conv(in, out);
    return 0;
}
