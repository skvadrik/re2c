// re2swift $INPUT -o $OUTPUT

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

/*!rules:re2c:colors
  *                            { fatalError("unreachable") }
  "red" | "salmon" | "magenta" { return .color }
*/

/*!rules:re2c:fish
  *                            { fatalError("unreachable") }
  "haddock" | "salmon" | "eel" { return .fish }
*/

func lex(_ yyinput: UnsafePointer<UInt8>) -> What {
  var yycursor = 0, yymarker = 0
  /*!re2c
    re2c:yyfill:enable = 0;

    !use:fish;
    !use:colors;
    * { return .dunno }  // Overrides inherited '*' rules
  */
}

enum What { case color, fish, dunno }

assert(lex("salmon") == .fish)
assert(lex("what?") == .dunno)
