// re2c $INPUT -o $OUTPUT -i8 --input-encoding utf8
#include <assert.h>

int lex(const char *YYCURSOR)
{
#define YYCTYPE unsigned char
    const char *YYMARKER;

    /*!re2c
    re2c:yyfill:enable = 0;

    end = "\x00";

    "Аня"  end { return 3; }
    "Маша" end { return 1; }
    "Уля"  end { return 2; }

    [Сс] "ерге" [а-яА-Я] end { return 0; }

    * { return -1; }
    */
}

int main()
{
    assert(lex("Аня") == 3);
    assert(lex("Маша") == 1);
    assert(lex("Уля") == 2);
    assert(lex("Сергей") == 0);
    assert(lex("Сергеы") == 0);
    assert(lex("сергеЫ") == 0);
    return 0;
}
