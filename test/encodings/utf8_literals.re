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
    "1"  end { return 4; } // 1byte U+31
    "~"  end { return 5; } // 1byte U+7E
    "ѷ"  end { return 6; } // 2bytes U+477
    "Έ"  end { return 7; } // 2bytes U+388
    "ｷ"  end { return 8; } // 3bytes U+FF77
    "ﾈ"  end { return 9; } // 3bytes U+FF88
    "𣝷"  end { return 10; } // 4bytes U+23777
    "𨢈"  end { return 11; } // 4bytes U+23888
    "𤰖"  end { return 12; } // 4bytes U+24C16
    "𝌒"  end { return 13; } // 4bytes U+1D312

    [Сс] "ерге" [а-яА-Я] end { return 0; }

    * { return -1; }
    */
}

#define TEST(s, i) assert(lex(s) == i)

int main()
{
    TEST("Аня", 3);
    TEST("Маша", 1);
    TEST("Уля", 2);
    TEST("1", 4);
    TEST("~", 5);
    TEST("ѷ", 6);
    TEST("Έ", 7);
    TEST("ｷ", 8);
    TEST("ﾈ", 9);
    TEST("𣝷", 10);
    TEST("𨢈", 11);
    TEST("𤰖", 12);
    TEST("𝌒", 13);
    TEST("Сергей", 0);
    TEST("Сергеы", 0);
    TEST("сергеЫ", 0);
    return 0;
}
