// re2java $INPUT -o $OUTPUT

class Main {
    /*!max:re2c*/

    // Expects yymaxfill-padded string.
    static int lex(String str) {
        // Pad string with yymaxfill zeroes at the end.
        byte[] yyinput = new byte[str.length() + YYMAXFILL];
        System.arraycopy(str.getBytes(), 0, yyinput, 0, str.length()); 

        int yycursor = 0;
        int yylimit = yyinput.length;
        int count = 0;

        loop: while (true) {
            /*!re2c
                re2c:YYCTYPE = "byte";
                re2c:YYPEEK = "yyinput[yycursor]";
                re2c:YYFILL = "return -1;";

                str = ['] ([^'\\] | [\\][^])* ['];

                [\x00] {
                    // Check that it is the sentinel, not some unexpected null.
                    return (yycursor - 1 == str.length()) ? count : -1;
                }
                str  { count += 1; continue loop; }
                [ ]+ { continue loop; }
                *    { return -1; }
            */
        }
    }

    public static void main(String []args) {
        assert lex("") == 0;
        assert lex("'qu\0tes' 'are' 'fine: \\'' ") == 3;
        assert lex("'unterminated\\'") == -1;
        assert lex("'unexpected \00 null\\'") == -1;
    }
};
