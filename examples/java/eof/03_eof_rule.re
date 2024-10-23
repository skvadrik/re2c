// re2java $INPUT -o $OUTPUT

class Main {
    // Expects a null-terminated string.
    static int lex(String yyinput) {
        int yycursor = 0;
        int yymarker = 0;
        int yylimit = yyinput.length() - 1; // yylimit points at the terminating null
        int count = 0;

        loop: while (true) {
            /*!re2c
                re2c:YYCTYPE = "char";
                re2c:YYPEEK = "yyinput.charAt(yycursor)";
                re2c:yyfill:enable = 0;
                re2c:eof = 0;

                str = ['] ([^'\\] | [\\][^])* ['];

                *    { return -1; }
                $    { return count; }
                str  { count += 1; continue loop; }
                [ ]+ { continue loop; }
            */
        }
    }

    public static void main(String []args) {
        assert lex("\0") == 0;
        assert lex("'qu\0tes' 'are' 'fine: \\'' \0") == 3;
        assert lex("'unterminated\\'\0") == -1;
    }
};
