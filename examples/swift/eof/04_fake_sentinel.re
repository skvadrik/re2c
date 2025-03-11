// re2swift $INPUT -o $OUTPUT
import Foundation

func lex(_ str: Data) -> Int? {
  var cursor = 0, limit = str.count
  var count = 0

  loop: while true {
    /*!re2c
      re2c:api = generic;
      re2c:yyfill:enable = 0;
      re2c:YYSKIP = "cursor += 1";
      re2c:YYPEEK = "cursor < limit ? str[cursor] : 0";  // fake null

      [a-z]+ {
        count += 1
        continue loop
      }
      [\x00] { return count }
      [ ]+   { continue loop }
      *      { return nil}
    */
  }
}

func test(_ str: String, _ expect: Int?) {
  // For the sake of example create a string without terminating null.
  assert(lex(Data(str.utf8)) == expect)
}

test("", 0)
test("one two three ", 3)
test("f0ur", nil)
