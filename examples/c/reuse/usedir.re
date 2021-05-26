// re2c $INPUT -o $OUTPUT

// This example shows how to combine reusable re2c blocks with the
// use directive. Two rules blocks ('colors' and 'fish') are merged
// into one re2c block. The rule for 'salmon' occurs in both blocks;
// the 'fish' block takes priority because it is used earlier.

#include <assert.h>

enum What { COLOR, FISH, DUNNO };

/*!rules:re2c:colors
    "red" | "salmon" | "magenta" { return COLOR; }
*/

/*!rules:re2c:fish
    "swordfish" | "salmon" | "haddock" { return FISH; }
*/

static What lex(const char *YYCURSOR)
{
    const char *YYMARKER;
    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = char;

    !use:fish;
    !use:colors;
    * { return DUNNO; }
    */
}

int main()
{
    assert(lex("salmon") == FISH);
    return 0;
}
