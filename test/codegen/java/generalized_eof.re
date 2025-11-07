// re2java $INPUT -o $OUTPUT

/*!rules:re2c:x
    re2c:YYCTYPE = int;
    re2c:YYPEEK = "Byte.toUnsignedInt(yyinput[yycursor])";

    $           { return 0; }
    *           { return 1; }
    [a] $       { return 2; }
    [a]         { return 3; }
    [b] $ | [b] { return 4; }
    [c]+ $      { return 5; }
*/

class Main {
    static int lex_simple(byte[] yyinput) {
        int yycursor = 0;
        int yymarker = 0;
        int yylimit = yyinput.length - 1;

        /*!use:re2c:x
            re2c:yyfill:enable = 0;
        */
    }

    static int lex_eof(byte[] yyinput) {
        int yycursor = 0;
        int yymarker = 0;
        int yylimit = yyinput.length - 1;

        /*!use:re2c:x
            re2c:eof = 0;
            re2c:YYFILL = "false"; // always fails
            re2c:YYEND = "yycursor == yylimit";
        */
    }

    /*!max:re2c*/

    static int lex_scc(byte[] str) {
        int yycursor = 0;
        int yymarker = 0;
        int len = str.length - 1; // skip terminating null
        int yylimit = len + YYMAXFILL;

        byte[] yyinput = new byte[yylimit];
        System.arraycopy(str, 0, yyinput, 0, len);

        /*!use:re2c:x
            re2c:YYFILL = "return -1;"; // always fails
            re2c:YYEND = "yycursor == len";
        */
    }

    static void test(byte[] str, int retval) {
        assert lex_simple(str) == retval;
        assert lex_eof(str) == retval;
        assert lex_scc(str) == retval;
    }

    public static void main(String []args) {
        test("\0".getBytes(), 0);
        test("a\0".getBytes(), 2);
        test("ax\0".getBytes(), 3);
        test("b\0".getBytes(), 4);
        test("bx\0".getBytes(), 4);
        test("ccc\0".getBytes(), 5);
    }
};
