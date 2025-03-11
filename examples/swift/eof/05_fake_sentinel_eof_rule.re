// re2swift $INPUT -o $OUTPUT
import Foundation

func lex(_ str: Data) -> Int? {
  var cursor = 0, limit = str.count, marker = 0
  var count = 0

  loop: while true {
    /*!re2c
      re2c:api = generic;
      re2c:eof = 0;
      re2c:yyfill:enable = 0;
      re2c:YYPEEK     = "cursor < limit ? str[cursor] : 0";  // fake null
      re2c:YYSKIP     = "cursor += 1";
      re2c:YYBACKUP   = "marker = cursor";
      re2c:YYRESTORE  = "cursor = marker";
      re2c:YYLESSTHAN = "limit <= cursor";

      str = ['] ([^'\\] | [\\][^])* ['];

      str  {
        count += 1
        continue loop
      }
      [ ]+ { continue loop }
      $    { return count }
      *    { return nil}
    */
  }
}

func test(_ str: String, _ expect: Int?) {
  // For the sake of example create a string without terminating null.
  assert(lex(Data(str.utf8)) == expect)
}

test("", 0)
test("'qu\0tes' 'are' 'fine: \\'' ", 3)
test("'unterminated\\'", nil)
