#include <assert.h>

enum Num {ERR, BIN, OCT, DEC, HEX};

static Num lex(const char *YYCURSOR)
{
    const char *YYMARKER;
    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = char;

    end = "\x00";
    bin = '0b' [01]+;
    oct = "0" [0-7]*;
    dec = [1-9][0-9]*;
    hex = '0x' [0-9a-fA-F]+;

    *       { return ERR; }
    bin end { return BIN; }
    oct end { return OCT; }
    dec end { return DEC; }
    hex end { return HEX; }
    */
}

int main()
{
    assert(lex("") == ERR);
    assert(lex("0b1101") == BIN);
    assert(lex("0644") == OCT);
    assert(lex("1234567890") == DEC);
    assert(lex("0x7ef") == HEX);
    return 0;
}
