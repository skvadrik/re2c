// re2swift $INPUT -o $OUTPUT -i --api simple

func lex(_ yyinput: UnsafePointer<UInt8>) -> Bool {
  var yycursor = 0
  /*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYCTYPE = UInt8;

    [1-9][0-9]* { return true }
    *           { return false }
  */
}

@main struct Program {
  static func main() {
    let string: StaticString = "1234"
    assert(lex(string.utf8Start))
  }
}
