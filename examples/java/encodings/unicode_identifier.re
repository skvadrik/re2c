// re2java $INPUT -o $OUTPUT --utf8 -s

/*!include:re2c "unicode_categories.re" */

class Main {
    static boolean lex(String yyinput) {
        int yycursor = 0;
        int yymarker = 0;

        /*!re2c
            re2c:YYCTYPE = "char";
            re2c:YYPEEK = "yyinput.charAt(yycursor)";
            re2c:yyfill:enable = 0;

            // Simplified "Unicode Identifier and Pattern Syntax"
            // (see https://unicode.org/reports/tr31)
            id_start    = L | Nl | [$_];
            id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
            identifier  = id_start+;
            // It should be `id_start id_continue*`, but that causes `error: code too large`

            identifier { return true; }
            *          { return false; }
        */
    }

    public static void main(String []args) {
        assert lex("_Ыдентификатор\0");
    }
};
