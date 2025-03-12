// re2swift $INPUT -o $OUTPUT -i --api simple

func lex(_ yyinput: UnsafeBufferPointer<UInt8>) -> Bool {
  var yycursor = 0, yymarker = 0
  /*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = UInt8;

    "\a\b\t\n\v\f\r\"\\" { return true }
    * {
      let _: [UnicodeScalar] = [ "\u{7}", "\u{8}", "\t", "\n", "\u{B}", "\u{C}", "\r", "\"", "\\" ]
      return false
    }
  */
}

@main struct Program {
  static func main() {
    let test: StaticString = "\u{07}\u{08}\u{09}\u{0A}\u{0B}\u{0C}\u{0D}\u{22}\u{5C}\0"
    test.withUTF8Buffer {
      assert(lex($0))
    }
  }
}
