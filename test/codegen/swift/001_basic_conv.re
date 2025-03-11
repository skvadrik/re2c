// re2swift $INPUT -o $OUTPUT

func lex(_ yyinput: UnsafeBufferPointer<UInt8>) -> Bool {
  var yycursor = 0

  /*!re2c
    re2c:yyfill:enable = 0;
    re2c:yych:conversion = 1;
    re2c:YYCTYPE = Int8;

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
