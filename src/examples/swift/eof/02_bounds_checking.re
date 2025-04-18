// re2swift $INPUT -o $OUTPUT

/*!max:re2c*/

func lex(_ str: UnsafeBufferPointer<UInt8>) -> Int? {
  let length = str.count

  // Make a copy of the string with YYMAXFILL zeroes at the end.
  let yyinput = ContiguousArray<UInt8>(str) + repeatElement(0, count: yymaxfill)

  var yycursor = 0, yylimit = length + yymaxfill
  var count = 0

  loop: while true {
    /*!re2c
      re2c:YYFILL  = "return nil";

      str = ['] ([^'\\] | [\\][^])* ['];

      str {
        count += 1
        continue loop
      }
      [\x00] {
        // Check that it's the sentinel, not some unexpected null.
        if yycursor - 1 == length { return count } else { return nil }
      }
      [ ]+ { continue loop }
      *    { return nil }
    */
  }
}

func test(_ str: StaticString, _ expect: Int?) {
  str.withUTF8Buffer {
    assert(lex($0) == expect)
  }
}

test("", 0)
test("'qu\0tes' 'are' 'fine: \\'' ", 3)
test("'unterminated\\'", nil)
test("'unexpected \0 null\\'", nil)
