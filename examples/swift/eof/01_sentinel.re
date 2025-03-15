// re2swift $INPUT -o $OUTPUT --api simple

// Expects a null-terminated string.
func lex(_ yyinput: UnsafePointer<UInt8>) -> Int? {
  var yycursor = 0, count = 0

  loop: while true {
    /*!re2c
      re2c:yyfill:enable = 0;

      [a-z]+ {
        count += 1
        continue loop
      }
      [ ]+   { continue loop }
      [\x00] { return count }
      *      { return nil }
    */
  }
}

@main struct Program {
  static func main() {
    let test = { (str: StaticString, expect: Int?) in
      assert(lex(str.utf8Start) == expect)
    }
    test("", 0)
    test("one two three", 3)
    test("f0ur", nil)
  }
}
