// re2swift $INPUT -o $OUTPUT -i -d

func lex(_ string: UnsafeBufferPointer<UInt8>) -> Bool {
  var cursor = 0, marker = 0
  var yych: UInt8 = 0

  let yypeek    = { string[cursor] }
  let yyskip    = { cursor += 1 }
  let yybackup  = { marker = cursor }
  let yyrestore = { cursor = marker }
  let yydebug   = { print("lex: char '\(UnicodeScalar(yych))'") }

  /*!re2c
    re2c:api:style = functions;
    re2c:define:YYCTYPE = UInt8;
    re2c:yych:emit = 0;
    re2c:yyfill:enable = 0;

    alpha  = [A-Za-z];
    number = [0-9];

    level = alpha number alpha number;
    name  = (alpha | number | " ")+;

    level [;] name { return true }
    *              { return false }
  */
}

@main struct Program {
  static func main() {
    let test: StaticString = "e1m1;Hanger\0"
    test.withUTF8Buffer {
      assert(lex($0))
    }
  }
}
