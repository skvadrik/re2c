// re2swift $INPUT -o $OUTPUT -i
// Test that re2c is able to lex Swift code with braces and backticks.

func lex(_ yyinput: UnsafeBufferPointer<UInt8>) -> Int {
  var yycursor = 0
  /*!re2c
    re2c:yyfill:enable = 0;

    [1-9][0-9]* {
      let `class` = 1234
      if (`class`) == 1234 {
        return `class`
      }
    }
    * { return 0 }
  */
}

@main struct Program {
  static func main() {
    let test: StaticString = "1234\0"
    test.withUTF8Buffer {
      assert(lex($0) == 1234)
    }
  }
}
