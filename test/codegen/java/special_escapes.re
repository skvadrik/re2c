// re2java $INPUT -o $OUTPUT

class Main {
    static boolean lex(String yyinput) {
        int yycursor = 0;
        int yymarker = 0;

        /*!re2c
            re2c:YYCTYPE = "char";
            re2c:YYPEEK = "yyinput.charAt(yycursor)";
            re2c:yyfill:enable = 0;

            "\a\b\f\n\r\t\v\\'\"" { return true; }
            * {
                char[] x = {'\b', '\f', '\n', '\r', '\t', '\\', '\'', '\"'};
                return false;
            }
        */
    }

    public static void main(String []args) {
        assert lex("\007\010\014\012\015\011\013\\'\"\0");
    }
};
