// re2java $INPUT -o $OUTPUT

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

/*!rules:re2c:colors
    *                            { throw new IllegalArgumentException("ah"); }
    "red" | "salmon" | "magenta" { return Ans.COLOR; }
*/

/*!rules:re2c:fish
    *                            { throw new IllegalArgumentException("oh"); }
    "haddock" | "salmon" | "eel" { return Ans.FISH; }
*/

class Main {
    enum Ans {COLOR, FISH, DUNNO};

    static Ans lex(String yyinput) { // no-throw, as '*' rules are overridden
        int yycursor = 0;
        int yymarker = 0;

        /*!re2c
            re2c:yyfill:enable = 0;
            re2c:YYCTYPE = "char";
            re2c:YYPEEK = "yyinput.charAt(yycursor)";

            !use:fish;
            !use:colors;
            * { return Ans.DUNNO; } // overrides inherited '*' rules
        */
    }

    public static void main(String []args) {
        assert lex("salmon") == Ans.FISH;
        assert lex("what?") == Ans.DUNNO;
    }
};
