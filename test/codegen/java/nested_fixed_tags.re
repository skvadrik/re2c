// re2java $INPUT -o $OUTPUT

/*!re2c
    re2c:api = custom;
    re2c:define:YYCTYPE     = "char";
    re2c:define:YYPEEK      = "str.charAt(cur)";
    re2c:define:YYSKIP      = "cur += 1;";
    re2c:define:YYBACKUP    = "mar = cur;";
    re2c:define:YYRESTORE   = "cur = mar;";
    re2c:define:YYSTAGP     = "@@{tag} = cur;";
    re2c:define:YYSTAGN     = "@@{tag} = -1;";
    re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift};";
    re2c:yyfill:enable = 0;
*/

class Main {
    /*!maxnmatch:re2c*/

    static int lex_tags(String str) {
        int cur = 0, mar = 0, x, y;
        /*!stags:re2c format = "int @@ = -1;\n"; */
        /*!re2c
            re2c:tags = 1;
            ([b] @x [a] @y)? { return (x == -1) ? -1 : y - x; }
        */
    }

    static int lex_captures(String str) {
        int cur = 0, yynmatch;
        int[] yypmatch = new int[YYMAXNMATCH * 2];
        /*!stags:re2c format = "int @@ = -1;\n"; */
        /*!re2c
            re2c:posix-captures = 1;
            (([a]))? { return yypmatch[4]; }
        */
    }

    public static void main(String []args) {
        assert lex_tags("\0") == -1;
        assert lex_tags("ba\0") == 1;
        assert lex_captures("\0") == -1;
        assert lex_captures("a\0") == 0;
    }
};
