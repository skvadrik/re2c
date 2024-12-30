// re2js $INPUT -o $OUTPUT

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

const COLOR = 1
const FISH = 2
const DUNNO = 3

/*!rules:re2c:colors
    *                            { throw "ah" }
    "red" | "salmon" | "magenta" { return COLOR }
*/

/*!rules:re2c:fish
    *                            { throw "oh" }
    "haddock" | "salmon" | "eel" { return FISH }
*/

function lex(yyinput) {
    let yycursor = 0
    /*!re2c
        re2c:yyfill:enable = 0;

        !use:fish;
        !use:colors;
        * { return DUNNO } // overrides inherited '*' rules
    */
}

function test(s, n) { if (lex(s) != n) throw "error!"; }

test("salmon", FISH)
test("what?", DUNNO)
