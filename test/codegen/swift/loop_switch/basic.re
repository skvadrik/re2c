// re2swift $INPUT -o $OUTPUT --loop-switch -i

func lex(_ str: UnsafeBufferPointer<UInt8>) -> Bool {
  var cursor = 0

  /*!re2c
    re2c:yyfill:enable  = 0;
    re2c:define:YYCTYPE = UInt8;
    re2c:define:YYPEEK = "str[cursor]";
    re2c:define:YYSKIP = "cursor += 1";

    alpha = [a-zA-Z];
    ident = alpha (alpha | [0-9])*;

    ident { return true }
    *     { return false }
  */
}

@main struct Program {
  static func main() {
    let s: StaticString = "qwerty42\0"
    s.withUTF8Buffer {
      assert(lex($0))
    }
  }
}
