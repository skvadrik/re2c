// re2java $INPUT -o $OUTPUT -s

class Main {
    static boolean lex(String str) {
        int cur = 0;

        /*!re2c
            re2c:api = custom;
            re2c:define:YYCTYPE = "char";
            re2c:define:YYPEEK = "str.charAt(cur)";
            re2c:define:YYSKIP = "cur += 1;";
            re2c:yyfill:enable = 0;

            number = [1-9][0-9]*;

            number { return true; }
            *      { return false; }
        */
    }

    public static void main(String []args) {
        assert lex("1234\0");
    }
};
