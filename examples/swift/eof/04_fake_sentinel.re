// re2swift $INPUT -o $OUTPUT
import Foundation

func lex(_ str: Data) -> Int? {
  let length = str.count

  var cursor = 0, limit = length
  var count = 0

  loop: while true {
    /*!re2c
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

@main struct Program {
  static func main() {
    let test = { (str: String, expect: Int?) in
      // For the sake of example create a string without terminating null.
      assert(lex(Data(str.utf8)) == expect)
    }
    test("", 0)
    test("one two three ", 3)
    test("f0ur", nil)
  }
}
