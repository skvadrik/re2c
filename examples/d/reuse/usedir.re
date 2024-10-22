// re2d $INPUT -o $OUTPUT
module main;

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

enum What { COLOR, FISH, DUNNO };

/*!rules:re2c:colors
    *                            { assert(false); }
    "red" | "salmon" | "magenta" { return What.COLOR; }
*/

/*!rules:re2c:fish
    *                            { assert(false); }
    "haddock" | "salmon" | "eel" { return What.FISH; }
*/

private What lex(const(char)* s) {
    const(char)* yycursor = s, yymarker;
    /*!re2c
        re2c:YYCTYPE = "char";
        re2c:yyfill:enable = 0;

        !use:fish;
        !use:colors;
        * { return What.DUNNO; } // overrides inherited '*' rules
    */
}

void main() {
    assert(lex("salmon") == What.FISH);
    assert(lex("what?") == What.DUNNO);
}
