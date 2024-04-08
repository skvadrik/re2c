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

fn lex(str string) What {
    mut cur, mut mar := 0, 0
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE   = u8;
        re2c:define:YYPEEK    = "str[cur]";
        re2c:define:YYSKIP    = "cur += 1";
        re2c:define:YYBACKUP  = "mar = cur";
        re2c:define:YYRESTORE = "cur = mar";

        !use:fish;
        !use:colors;
        * { return .dunno }  // overrides inherited '*' rules
    */
}

fn main() {
    assert lex("salmon") == .fish
    assert lex("what?") == .dunno
}
