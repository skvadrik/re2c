// re2swift $INPUT -o $OUTPUT --api generic -d

func lex(_ s: UnsafeBufferPointer<UInt8>) -> Bool {
  var cursor = 0, marker = 0

  /*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYPEEK = "s[cursor]";
    re2c:YYSKIP = "cursor += 1";
    re2c:YYBACKUP  = "marker = cursor";
    re2c:YYRESTORE = "cursor = marker";
    re2c:YYDEBUG = "print(\"lex: '\\(@@{char})' int state \\(@@{state})\")";

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
