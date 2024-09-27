// re2v $INPUT -o $OUTPUT

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

enum What {
    color
    fish
    dunno
}

/*!rules:re2c:colors
    *                            { panic("eh!") }
    "red" | "salmon" | "magenta" { return .color }
*/

/*!rules:re2c:fish
    *                            { panic("oh!") }
    "haddock" | "salmon" | "eel" { return .fish }
*/

fn lex(yyinput string) What {
    mut yycursor, mut yymarker := 0, 0
    /*!re2c
        re2c:yyfill:enable = 0;

        !use:fish;
        !use:colors;
        * { return .dunno }  // overrides inherited '*' rules
    */
}

fn main() {
    assert lex("salmon") == .fish
    assert lex("what?") == .dunno
}
