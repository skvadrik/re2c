// re2swift $INPUT -o $OUTPUT -d

func lex(_ s: UnsafeBufferPointer<UInt8>) -> Bool {
  var cursor = 0, marker = 0

  /*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = UInt8;
    re2c:define:YYPEEK = "s[cursor]";
    re2c:define:YYSKIP = "cursor += 1";
    re2c:define:YYBACKUP  = "marker = cursor";
    re2c:define:YYRESTORE = "cursor = marker";
    re2c:define:YYDEBUG = "print(\"lex: '\\(@@{char})' int state \\(@@{state})\")";

    end = [\x00];

    [0-9]+ end { return true }
    *          { return false }
  */
}

@main struct Program {
  static func main() {
    let s: StaticString = "123\0"
    s.withUTF8Buffer {
      assert(lex($0), "expected 123")
    }
  }
}
