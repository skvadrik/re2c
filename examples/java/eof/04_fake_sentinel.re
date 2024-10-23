// re2java $INPUT -o $OUTPUT

class Main {
    // Expects a string without terminating null.
    static int lex(String str) {
        byte[] yyinput = str.getBytes();
        int yycursor = 0;
        int count = 0;

        loop: while (true) {
            /*!re2c
                re2c:api = generic;
                re2c:YYCTYPE = "byte";
                re2c:YYPEEK = "(yycursor < yyinput.length) ? yyinput[yycursor] : 0";
                re2c:YYSKIP = "yycursor += 1;";
                re2c:yyfill:enable = 0;

                *      { return -1; }
                [\x00] { return count; }
                [a-z]+ { count += 1; continue loop; }
                [ ]+   { continue loop; }
            */
        }
    }

    public static void main(String []args) {
        assert lex("") == 0;
        assert lex("one two three") == 3;
        assert lex("f0ur") == -1;
    }
};
