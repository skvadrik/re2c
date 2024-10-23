// re2java $INPUT -o $OUTPUT

/*!include:re2c "definitions.java" */

class Main {
    enum Num {INT, FLOAT, NAN};

    static Num lex(String yyinput) {
        int yycursor = 0;
        int yymarker = 0;

        /*!re2c
            re2c:YYCTYPE = "char";
            re2c:YYPEEK = "yyinput.charAt(yycursor)";
            re2c:yyfill:enable = 0;

            *      { return Num.NAN; }
            number { return Num.INT; }
            !include "extra_rules.re.inc";
        */
    }

    public static void main(String []args) {
        assert lex("123\0") == Num.INT;
        assert lex("123.4567\0") == Num.FLOAT;
    }
};
