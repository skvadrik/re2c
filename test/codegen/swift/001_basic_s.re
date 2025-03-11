// re2swift $INPUT -o $OUTPUT --api generic -s

func lex(_ string: UnsafeBufferPointer<UInt8>) -> Bool {
  var cursor = 0
  /*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYCTYPE = UInt8;
    re2c:YYPEEK = "string[cursor]";
    re2c:YYSKIP = "cursor += 1";

    [1-9][0-9]* { return true }
    *           { return false }
  */
}

@main struct Program {
  static func main() {
    let test: StaticString = "1234\0"
    test.withUTF8Buffer {
      assert(lex($0))
    }
  }
}
