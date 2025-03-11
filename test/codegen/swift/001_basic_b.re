// re2swift $INPUT -o $OUTPUT --api generic -b

func lex(_ s: UnsafeBufferPointer<UInt8>) -> Bool {
  var cursor = 0
  /*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYPEEK = "s[cursor]";
    re2c:YYSKIP = "cursor += 1";

    number = [1-9][0-9]*;

    number { return true }
    *      { return false }
  */
}

@main struct Program {
  static func main() {
    let s: StaticString = "1234\0"
    s.withUTF8Buffer {
      assert(lex($0))
    }
  }
}
