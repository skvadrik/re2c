// re2swift $INPUT -o $OUTPUT

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

func test(_ str: StaticString, _ expect: Int?) {
  assert(lex(str.utf8Start) == expect)
}

test("", 0)
test("one two three", 3)
test("f0ur", nil)
