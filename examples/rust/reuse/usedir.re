// re2rust $INPUT -o $OUTPUT --api simple

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

#[derive(Debug, PartialEq)]
enum Ans { Color, Fish, Dunno }

/*!rules:re2c:colors
    *                            { panic!("ah"); }
    "red" | "salmon" | "magenta" { return Ans::Color; }
*/

/*!rules:re2c:fish
    *                            { panic!("oh"); }
    "haddock" | "salmon" | "eel" { return Ans::Fish; }
*/

fn lex(yyinput: &[u8]) -> Ans {
    assert!(yyinput.len() > 0); // expect nonempty input

    let (mut yycursor, mut yymarker) = (0, 0);
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:YYCTYPE = u8;

        !use:fish;
        !use:colors;
        * { return Ans::Dunno; }  // overrides inherited '*' rules
    */
}

fn main() {
    assert_eq!(lex(b"salmon"), Ans::Fish);
    assert_eq!(lex(b"what?"), Ans::Dunno);
}
