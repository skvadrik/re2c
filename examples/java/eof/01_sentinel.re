// re2java $INPUT -o $OUTPUT

class Main {
    // Expects a null-terminated string.
    static int lex(String yyinput) {
        int yycursor = 0;
        int count = 0;

        loop: while (true) {
            /*!re2c
                re2c:YYCTYPE = "char";
                re2c:YYPEEK = "yyinput.charAt(yycursor)";
                re2c:yyfill:enable = 0;

                *      { return -1; }
                [\x00] { return count; }
                [a-z]+ { count += 1; continue loop; }
                [ ]+   { continue loop; }
            */
        }
    }

    public static void main(String []args) {
        assert lex("\0") == 0;
        assert lex("one two three\0") == 3;
        assert lex("f0ur\0") == -1;
    }
};
