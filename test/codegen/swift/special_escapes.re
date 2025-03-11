// re2swift $INPUT -o $OUTPUT -i

func lex(_ yyinput: UnsafeBufferPointer<UInt8>) -> Bool {
  var yycursor = 0, yymarker = 0
  /*!re2c
    re2c:yyfill:enable = 0;

    "\t\n\r\"'\\" { return true }
    * {
      let _: [UnicodeScalar] = [ "\t", "\n", "\r", "\"", "\'", "\\" ]
      return false
    }
  */
}

@main struct Program {
  static func main() {
    let test: StaticString = "\u{09}\u{0A}\u{0D}\u{22}\u{27}\u{5C}\0"
    test.withUTF8Buffer {
      assert(lex($0))
    }
  }
}
