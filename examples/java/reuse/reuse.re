// re2java $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.

/*!rules:re2c
    re2c:yyfill:enable = 0;
    re2c:YYPEEK = "yyinput[yycursor]";
    re2c:indent:top = 1;

    "∀x ∃y" { return true; }
    *       { return false; }
*/

class Main {
    static boolean lex_utf8(int[] yyinput) {
        int yycursor = 0;
        int yymarker = 0;
        /*!use:re2c
            re2c:YYCTYPE = "int"; // should be `byte`, but it's signed in Java
            re2c:encoding:utf8 = 1;
        */
    }

    static boolean lex_utf32(int[] yyinput) {
        int yycursor = 0;
        int yymarker = 0;
        /*!use:re2c
            re2c:YYCTYPE = "int";
            re2c:encoding:utf32 = 1;
        */
    }

    public static void main(String []args) {
        // we have to use `int`, because `byte`in Java cannot represent values greater than 127
        int[] s_utf8 = new int[]{0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79};
        assert lex_utf8(s_utf8);

        int[] s_utf32 = new int[]{0x2200, 0x78, 0x20, 0x2203, 0x79};
        assert lex_utf32(s_utf32);
    }
};
