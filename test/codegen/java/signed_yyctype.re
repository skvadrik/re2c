// re2java $INPUT -o $OUTPUT

import java.nio.charset.StandardCharsets;

/*!rules:re2c
    re2c:YYCTYPE = "int";
    re2c:yyfill:enable = 0;

    [\xff] { return true; }
    *      { return false; }
*/

class Main {
    static boolean lex_unsigned(byte[] yyinput) {
        int yycursor = 0;
        /*!use:re2c
            re2c:YYPEEK = "Byte.toUnsignedInt(yyinput[yycursor])";
        */
    }

    static boolean lex_signed(byte[] yyinput) {
        int yycursor = 0;
        /*!use:re2c
            re2c:YYPEEK = "yyinput[yycursor]"; // should be unsigned!
        */
    }

    public static void main(String []args) {
        assert lex_unsigned(("\u00ff\0").getBytes(StandardCharsets.ISO_8859_1));
        assert !lex_signed(("\u00ff\0").getBytes(StandardCharsets.ISO_8859_1)); // lexer works incorrectly
    }
};
