// re2java $INPUT -o $OUTPUT

class Main {
    static boolean lex(String yyinput) {
        int yycursor = 0;

        /*!re2c
            re2c:YYCTYPE = "char";
            re2c:YYPEEK = "yyinput.charAt(yycursor)";
            re2c:yyfill:enable = 0;

            [1-9][0-9]* { return true; }
            *           { return false; }
        */
    }

    public static void main(String []args) {
        assert lex("1234\0");
    }
};
