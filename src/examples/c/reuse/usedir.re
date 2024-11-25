// re2c $INPUT -o $OUTPUT
#include <assert.h>

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

typedef enum { COLOR, FISH, DUNNO } What;

/*!rules:re2c:colors
    *                            { assert(false); }
    "red" | "salmon" | "magenta" { return COLOR; }
*/

/*!rules:re2c:fish
    *                            { assert(false); }
    "haddock" | "salmon" | "eel" { return FISH; }
*/

static What lex(const char *s) {
    const char *YYCURSOR = s, *YYMARKER;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        !use:fish;
        !use:colors;
        * { return DUNNO; }  // overrides inherited '*' rules
    */
}

int main() {
    assert(lex("salmon") == FISH);
    assert(lex("what?") == DUNNO);
    return 0;
}
